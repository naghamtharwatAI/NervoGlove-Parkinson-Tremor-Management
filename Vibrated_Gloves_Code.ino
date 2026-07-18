#include <Wire.h>
#include <MPU6050.h>
#include <BluetoothSerial.h>

MPU6050 mpu;
BluetoothSerial SerialBT;

#define NUM_MOTORS 5
int motorPins[NUM_MOTORS] = {12, 13, 27, 26, 32};

#define BATTERY_PIN 34  // ADC pin connected to voltage divider from battery

int vibrationFrequency = 1;
int pulseCount = 3;
int pulseDuration = 200;
float tremorThreshold = 15000.0;
bool motorsEnabled = true;

bool isPulsing = false;
unsigned long pulseStartTime;
int pulsesRemaining = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("VibratedGlove");
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  for (int i = 0; i < NUM_MOTORS; i++) {
    pinMode(motorPins[i], OUTPUT);
  }

  pinMode(BATTERY_PIN, INPUT);
  Serial.println("Device Initialized.");
}

void loop() {
  static unsigned long lastUpdateTime = 0;
  unsigned long currentTime = millis();

  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float intensity = calculateTremorIntensity(gx, gy, gz, ax, ay, az);

  if (intensity > tremorThreshold && motorsEnabled && !isPulsing) {
    startPulsing();
  }

  handlePulsing();

  if (currentTime - lastUpdateTime > 1000) {
    lastUpdateTime = currentTime;

    float batteryVoltage = readBatteryVoltage();
    int batteryLevel = getBatteryPercentage(batteryVoltage);

    sendData(intensity, batteryLevel);
    plotData(intensity, gx, gy, gz, ax, ay, az, batteryVoltage, batteryLevel);

    if (batteryLevel <= 20) {
      SerialBT.println("⚠️ LOW BATTERY: " + String(batteryLevel) + "% - Please Recharge!");
      Serial.println("⚠️ LOW BATTERY: " + String(batteryLevel) + "% - Please Recharge!");
    }
  }

  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    handleCommand(command);
  }
}

float calculateTremorIntensity(int16_t gx, int16_t gy, int16_t gz,
                               int16_t ax, int16_t ay, int16_t az) {
  float gyroMag = sqrt(pow(gx, 2) + pow(gy, 2) + pow(gz, 2));
  float accelMag = sqrt(pow(ax, 2) + pow(ay, 2) + pow(az, 2));
  return gyroMag * 0.7 + accelMag * 0.3;
}

String getTremorLevel(float intensity) {
  if (intensity > 20000) {
    return "High";
  } else if (intensity > 15000 && intensity <= 20000) {
    return "Medium";
  } else {
    return "Stable";
  }
}

void startPulsing() {
  isPulsing = true;
  pulsesRemaining = pulseCount;
  pulseStartTime = millis();
  activateMotors();
}

void handlePulsing() {
  if (!isPulsing) return;

  if (millis() - pulseStartTime >= pulseDuration) {
    deactivateMotors();
    pulsesRemaining--;

    if (pulsesRemaining > 0) {
      pulseStartTime = millis();
      activateMotors();
    } else {
      isPulsing = false;
    }
  }
}

void activateMotors() {
  for (int i = 0; i < NUM_MOTORS; i++) {
    analogWrite(motorPins[i], vibrationFrequency);
  }
}

void deactivateMotors() {
  for (int i = 0; i < NUM_MOTORS; i++) {
    analogWrite(motorPins[i], 0);
  }
}

float readBatteryVoltage() {
  int raw = analogRead(BATTERY_PIN);
  float voltage = (raw / 4095.0) * 3.3; // ADC reads 0-3.3V
  return voltage * 2.0; // Adjust for voltage divider (e.g., 100k/100k)
}

int getBatteryPercentage(float voltage) {
  float percentage = (voltage - 3.2) / (4.2 - 3.2) * 100.0;
  percentage = constrain(percentage, 0, 95);
  return (int)percentage;
}

void sendData(float intensity, int batteryLevel) {
  String icon = "🔋";
  if (batteryLevel >= 80) icon = "🔋";
  else if (batteryLevel >= 50) icon = "🔋";
  else if (batteryLevel >= 20) icon = "🪫";
  else icon = "🪫";

  String data = "Tremor: " + getTremorLevel(intensity) + " | Battery: " + icon + " " + String(batteryLevel) + "%";
  SerialBT.println(data);
}

void plotData(float intensity, int16_t gx, int16_t gy, int16_t gz,
              int16_t ax, int16_t ay, int16_t az, float voltage, int batteryLevel) {
  Serial.print("Tremor:");
  Serial.print(intensity);
  Serial.print(", Battery:");
  Serial.print(voltage);
  Serial.print("V (");
  Serial.print(batteryLevel);
  Serial.print("%), GyroX:");
  Serial.print(gx);
  Serial.print(", GyroY:");
  Serial.print(gy);
  Serial.print(", GyroZ:");
  Serial.print(gz);
  Serial.print(", AccelX:");
  Serial.print(ax);
  Serial.print(", AccelY:");
  Serial.print(ay);
  Serial.print(", AccelZ:");
  Serial.println(az);
}

void handleCommand(String command) {
  command.trim();
  if (command.startsWith("SET_FREQ")) {
    vibrationFrequency = command.substring(9).toInt();
    SerialBT.println("Frequency Set: " + String(vibrationFrequency) + "Hz");
  } else if (command.startsWith("SET_PULSES")) {
    int space1 = command.indexOf(' ');
    int space2 = command.indexOf(' ', space1 + 1);
    if (space1 != -1 && space2 != -1) {
      pulseCount = command.substring(space1 + 1, space2).toInt();
      pulseDuration = command.substring(space2 + 1).toInt();
      SerialBT.println("Pulses Set: " + String(pulseCount) + "x" + String(pulseDuration) + "ms");
    }
  } else if (command == "MOTORS_ON") {
    motorsEnabled = true;
    SerialBT.println("Motors Enabled");
  } else if (command == "MOTORS_OFF") {
    motorsEnabled = false;
    SerialBT.println("Motors Disabled");
  } else if (command == "STATUS") {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    float intensity = calculateTremorIntensity(gx, gy, gz, ax, ay, az);
    float voltage = readBatteryVoltage();
    int battery = getBatteryPercentage(voltage);
    SerialBT.println("STATUS:Tremor=" + getTremorLevel(intensity) + ",Battery=" + String(battery) + "%,Voltage=" + String(voltage, 2));
  } else {
    SerialBT.println("Invalid Command");
  }
}

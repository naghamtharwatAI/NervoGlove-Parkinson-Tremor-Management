# 🩺 NervoGlove
### AI-Powered Wearable Glove for Parkinson’s Tremor Management

![Uploading Banner of project.png…]()
---

## 📌 Overview

**NervoGlove** is a wearable healthcare device designed to help individuals with **Parkinson’s Disease** and other tremor-related neurological disorders manage hand tremors using **intelligent vibration feedback**.

The system combines **Embedded Systems, IoT, Mechatronics, Assistive Robotics, and Artificial Intelligence concepts** to provide real-time tremor detection and adaptive vibration stimulation.

The glove continuously monitors hand movement using an **MPU6050 IMU sensor** and activates **micro vibration motors** whenever abnormal tremor patterns are detected. A Bluetooth-connected mobile application allows users to monitor tremor intensity and customize vibration parameters in real time.

---

## 🎯 Problem Statement

Parkinson’s disease causes motor symptoms such as:

* Hand tremors
* Muscle stiffness
* Reduced coordination
* Difficulty performing daily activities

Current treatments may not fully control tremors for all patients. NervoGlove aims to provide a **non-invasive, affordable, and user-friendly assistive solution** that complements existing medical treatments.

---

## ✨ Key Features

* 🔄 **Real-time tremor detection**
* 📳 **Adaptive vibration feedback**
* 🎚 **Adjustable vibration intensity**
* ⏱ **Configurable pulse duration**
* 📱 **Bluetooth mobile application**
* 🔋 **Rechargeable battery system**
* 🧤 **Lightweight wearable design**
* 🧠 **AI-ready architecture for future personalization**

---

### Workflow

1. MPU6050 detects hand motion.
2. ESP32 processes sensor data.
3. Tremor intensity is calculated.
4. Vibration motors are activated when tremors exceed a threshold.
5. Data is transmitted to the mobile application via Bluetooth.
6. Users can adjust vibration settings and monitor device status.

---

## 🛠 Hardware Components

| Component                | Purpose                                   |
| ------------------------ | ----------------------------------------- |
| ESP32                    | Main controller & Bluetooth communication |
| MPU6050 IMU              | Motion and tremor detection               |
| 5 Micro Vibration Motors | Therapeutic vibration feedback            |
| Lithium Battery          | Portable power source                     |
| TP4056 Charger           | Safe battery charging                     |
| Breadboard & Wires       | Prototyping and testing                   |


## 💻 Software Stack

* **Arduino IDE**
* **C++**
* **MIT App Inventor**
* **Bluetooth Serial Communication**
* **Embedded Systems Programming**

---

## 📱 Mobile Application

The Android application was developed using **MIT App Inventor**.

### Main Features

* Bluetooth device scanning
* Connect/disconnect from the glove
* Live tremor intensity monitoring
* Battery status display
* Motor ON/OFF control
* Frequency level adjustment
* Pulse duration configuration

## 🧠 Tremor Detection Algorithm

The firmware uses a weighted combination of **gyroscope** and **accelerometer** data:

```cpp
float intensity = gyroMagnitude * 0.7 + accelMagnitude * 0.3;
```

This emphasizes gyroscope measurements because they are more reliable for detecting high-frequency tremor patterns.

---
# 📂 Repository Structure

```
NervoGlove
│
├── README.md
├── LICENSE
│
├── firmware
│   └── Vibrated_Gloves_Code.ino
│
├── mobile-app
│   ├── Vibrated_Glove1.aia
│   └── APK
│
├── hardware
│   ├── Circuit_Diagram
│
├── docs
│   └── Graduation_Project_Report.pdf
│
├── images
│   ├── cover.png
│   ├── signin_screen.jpg
│   ├── controller_screen.jpg
│   └── prototype.jpg
│
└── videos
    └── demo.mp4
```

---
## 🚀 Getting Started

### Hardware Setup

1. Connect the **MPU6050** to the ESP32 via I2C.
2. Connect the vibration motors to the designated GPIO pins.
3. Connect the battery through the **TP4056** charging module.
4. Upload the firmware using Arduino IDE.

### Firmware Upload

1. Install Arduino IDE.
2. Install the **ESP32 board package**.
3. Install required libraries:

   * Wire
   * MPU6050
   * BluetoothSerial
4. Open `firmware/Arduino_Code.ino`.
5. Select **ESP32 Dev Module**.
6. Upload the code.

### Mobile App

1. Install the APK from `mobile-app/APK/`.
2. Enable Bluetooth on your phone.
3. Open the app and connect to **VibratedGlove**.

---

## 📊 Current Prototype Results

The prototype successfully demonstrated:

* Real-time motion acquisition
* Tremor threshold detection
* Bluetooth communication with Android
* Configurable vibration feedback
* Stable wearable operation during testing sessions

---

## 🔬 Future Work

### AI Integration

* Machine learning-based tremor classification
* Personalized vibration patterns
* Adaptive therapy optimization

### Sensor Expansion

* EMG sensor integration
* Additional IMUs for finger-level analysis
* Higher-precision motion tracking

### Clinical & Product Development

* Extended clinical validation
* Custom PCB manufacturing
* Flutter cross-platform application
* Cloud-based patient monitoring
* Doctor dashboard and analytics

---

## 🏆 Achievements

* Final Year Project – Arab Open University (2024–2025)
* Biomedical & AI wearable healthcare research
* Assistive technology prototype development
* Patent-oriented product concept

---

## 👩‍💻 Author

**Nagham Tharwat**

* Artificial Intelligence Engineer
* Embedded Systems Developer
* Biomedical AI Researcher


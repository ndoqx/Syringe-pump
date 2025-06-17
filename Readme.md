# IoT Syringe Pump | Third-Year Embedded Project at KMITL

🔗 GitHub Repository: [ndoqx/Syringe-pump](https://github.com/ndoqx/Syringe-pump.git)

This project is a smart syringe pump designed during my third year as a Biomedical Engineering student at KMITL. Built with an ESP32, Ultrasonic Sensor, and a stepper motor driver, the system allows precise control of liquid infusion rate and volume via a mobile app (Blynk).

Users can remotely start, purge, or return the syringe motor while adjusting speed (ml/sec) and volume (ml) in real-time. Sensor feedback ensures controlled movement, and the system is designed for educational and prototyping use cases.

---

# Device Images

## Designed and constructed syringe pump

![Designed and constructed syringe pump](designed_constructed_syringe_pump.png)



---

# Features

* Remote Start / Purge / Return motor control via Blynk app
* Adjustable infusion volume (ml) and infusion speed (ml/sec)
* Ultrasonic distance sensor for real-time syringe tracking
* Stepper motor control via DIR/STEP/ENABLE pins
* Real-time monitoring via Blynk Terminal and Display Widgets
* LED status indicators for operation and alarm states
* Serial output for live debugging

---

# How It Works

1. User connects to the Blynk app.
2. Sets volume and speed through sliders.
3. Presses buttons to begin Start, Purge, or Return operation.
4. The system:
   Moves stepper motor accordingly
   Uses ultrasonic sensor to monitor piston/syringe distance
   Automatically stops based on volume input or max range
5. Displays values on Blynk and Serial Monitor.

---

# Hardware Used

| Component       | Description                                 |
| --------------- | ------------------------------------------- |
| ESP32 Dev Board | Core microcontroller with WiFi              |
| HC-SR04 Sensor  | Ultrasonic sensor to track syringe movement |
| Stepper Motor   | Mechanically drives syringe                 |
| Stepper Driver  | DIR, STEP, ENABLE pins (A4988 or similar)   |
| Blynk IoT App   | Remote control & monitoring                 |
| LED Indicator   | Visual feedback                             |
| Power Supply    | 12V supply for stepper + 5V for ESP32       |

---

# Wiring Overview

| Component      | ESP32 Pin |
| -------------- | --------- |
| DIR            | GPIO 22   |
| STEP           | GPIO 23   |
| ENABLE         | GPIO 21   |
| Trig (HC-SR04) | GPIO 12   |
| Echo (HC-SR04) | GPIO 13   |
| Status LED     | GPIO 2    |

---

# Code Overview

Main logic is in `Syringe Pump.ino`.
Key components:

* `MotorOneStep()`: Executes infusion cycle based on set volume.
* `MotorPurge()`: Runs forward until full.
* `MotorReturn()`: Runs in reverse until minimum.
* `myTimerEvent()`: Sends real-time data to Blynk.
* `BLYNK_WRITE()`: Handles volume, speed, and mode inputs.

---

# Installation & Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/ndoqx/Syringe-pump.git
   cd Syringe-pump
   ```

2. Open `Syringe Pump.ino` in Arduino IDE.

3. Install required libraries:

   * Blynk
   * HCSR04
   * WiFi (built-in for ESP32)

4. Replace Blynk credentials in the code with your own.

5. Upload the sketch to ESP32.

6. Use Blynk App to interact with the system.

---

# Blynk App Setup

| Widget       | Virtual Pin | Function             |
| ------------ | ----------- | -------------------- |
| Button       | V1          | Start Injection      |
| Button       | V2          | Purge Mode           |
| Button       | V3          | Return Mode          |
| Slider/Input | V4          | Volume (ml)          |
| Slider/Input | V5          | Speed (ml/sec)       |
| LED Widget   | V0, V6      | Status & Alarm LEDs  |
| Terminal     | V8          | Serial Output        |
| Display      | V7          | Injected Volume (ml) |

---

# Sample Output (Serial Monitor)

```
Syringe Pump Release 1.0
Volume : 2.5
Speed : 1.5
Delay : 0.3
Dist : 8.24 mlpersec Delay : 0.3
Motor: one step is working
Dist : 8.75
In max --- stop
```

---

# Future Improvements

* Add OLED or LCD for local status display
* Integrate alarm buzzer for alerts
* Replace ultrasonic with rotary encoder for higher precision
* Add calibration mode
* Enclose entire pump for user safety

---

# Author

**Thanetpol Noynuai**
Biomedical Engineering, KMITL (3rd Year Project)
🔗 GitHub: [@ndoqx](https://github.com/ndoqx)

---

# Disclaimer

This syringe pump is intended for academic and prototyping purposes only. It is **not approved for clinical or medical use**. Always validate with medical experts before real-world deployment.

---


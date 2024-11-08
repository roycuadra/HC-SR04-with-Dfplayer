# Intruder Detection System with DFPlayer Mini and Ultrasonic Sensor

This project utilizes an ultrasonic sensor to detect intruders based on distance and plays an alarm sound through the DFPlayer Mini module, all managed by a WeMos D1 Mini microcontroller.

## Components
- **WeMos D1 Mini**
- **DFPlayer Mini module**
- **Ultrasonic sensor** (e.g., HC-SR04)
- **Speaker** (connected to DFPlayer Mini)
- **Jumper wires**

## Pin Connections
- **Trig Pin** (Ultrasonic Sensor) → D5 on WeMos D1 Mini
- **Echo Pin** (Ultrasonic Sensor) → D6 on WeMos D1 Mini
- **RX Pin** (DFPlayer Mini) → D7 on WeMos D1 Mini
- **TX Pin** (DFPlayer Mini) → D8 on WeMos D1 Mini

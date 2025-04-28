# PIC16F877A bluetooth remote control car and collision warning - My first embedded system project

## Description

This project implements a Bluetooth-controlled remote car using the PIC16F877A microcontroller. The car is managed via an HC-05 Bluetooth module connected to a mobile app built with MIT App Inventor. An ultrasonic sensor (HC-SR04) measures the distance to obstacles in front of the car and triggers a visual warning, preventing collisions. A 16x02 I2C LCD displays the current speed level and movement status.

## Features

- **Bluetooth Remote Control:** Drive the car forward, backward, turn left, and turn right through Bluetooth commands (`F`, `B`, `L`, `R`) sent from the MIT App Inventor mobile app.
- **Adjustable Speed Levels:** Three preset speed modes (Slow, Normal, High) selectable via onboard buttons or Bluetooth commands (`1`, `2`, `3`).
- **Collision Warning System:** Ultrasonic sensor continuously measures distance; an LED buzzer provides visual feedback when an obstacle is detected within 30 cm. 
- **Display:** 16x02 I2C LCD on the car and Android app interface show current speed setting (`SLOW`/`NORMAL`/`HIGH`) and movement status (`FORWARD`/`BACK`/`LEFT`/`RIGHT`/`STOP`).
- **PWM Motor Control:** Smooth motor speed management via two PWM channels (CCP1, CCP2) and H-bridge outputs.
- **Mobile App Interface:** Android app (built with MIT App Inventor) featuring on-screen speed and directional buttons for Bluetooth control.

## Hardware Requirements

- **Microcontroller:** PIC16F877A
- **Bluetooth Module:** HC-05 or HC-06 (serial communication at 9600 baud)
- **Ultrasonic Sensor:** HC-SR04
- **Driver IC:** L298N or equivalent H-bridge for DC motor control
- **DC Motors:** Two geared DC motors with wheels
- **LCD Display:** 16x02 I2C LCD module 
- **Mobile App:** An Android phone
- **Power Supply:** 3 lithium batteries 3.7V<sub>DC</sub>, LM2596S

## Wiring & Schematics

<Contact me: 📧 dangnguyetanh1908@gmail.com to take schematic>

## Software Requirements

- CCS C Compiler
- src: `16f877a_finger-print_sim-module.c`

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/dangnguyetanh-public/PIC16F877A_HC-05_HC-SR04_DC-motors.git
   ```
2. Edit `config.h` with your phone number, I²C addresses, LCD pin, button pin, buzzer pin, etc.
3. Compile the code in CCS C Compiler 

4. Flash the HEX to PIC16F877A using PICKIT.

## Usage

1. **Power and Pairing**  
   - Insert three 3.7 V lithium batteries in series (≈12 V<sub>DC</sub> total) and switch on the main power; the LM2596S will regulate 5V<sub>DC</sub> to the PIC16F877A and peripherals. 
   - Also feed those 12 V<sub>DC</sub> into L298N module.
   - On your Android phone, enable Bluetooth, search for new devices, select **HC-05**, and enter the default PIN **1234** to pair :contentReference[oaicite:0]{index=0}.

2. **Install the Mobile App**  
   - Download **`car.apk`** from the repository to your Android phone.   

3. **Connect via Bluetooth**  
   - Open **car.apk**.  
   - Tap the **Bluetooth icon** in the top bar to scan for devices, select **HC-05**, and enter PIN **1234** if prompted.  
   - Once connected, the top bar will display **DISCONNECT** in red (tap it to disconnect when finished).

4. **Drive the Car**  
   - **Speed Level**: Tap **Slow**, **Normal**, or **High** to send `1`, `2`, or `3` and change the speed mode.  
   - **Direction Controls**:  
     - **↑** (Forward) sends `F`  
     - **←** (Left) sends `L`  
     - **→** (Right) sends `R`  
     - **↓** (Backward) sends `B`  
   - The app and 16×02 I2C LCD on the car updates to show the current speed mode and movement status.

5. **Shutdown**  
   - In **car.apk**, tap **DISCONNECT** before closing the app.  
   - Turn off the car’s main power switch to cut all power safely.

## Configuration

Sensitive settings (pin, etc.) are defined in `config.h` to avoid hardcoding in `16f877a_bluetooth_remote-control-car.c`.


## Contributing

Contributions are welcome! Please open an issue or submit a pull request for enhancements or bug fixes.


## Authors

- DANG NGUYET ANH  📧 Contact me: dangnguyetanh1908@gmail.com


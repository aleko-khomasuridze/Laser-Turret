# Laser Turret Receiver Arduino Sketch

This Arduino sketch transforms your Arduino into a "Laser Turret Receiver," allowing you to control servo motors wirelessly using a Bluetooth module. The ServoTimer2 library is employed to resolve conflicts with the standard Servo library when using the SoftwareSerial library. The Bluetooth module communicates with the Arduino through SoftwareSerial, and servo signals are generated using Timer2.

## Hardware Configuration

### Bluetooth Module
- Connect the Bluetooth module to pins 8 (RX) and 9 (TX) on the Arduino.

### Laser Turret Servo Motors
- Connect servo motors to pins 5 and 6 on the Arduino (extendable up to 8 servos).

## Instructions

1. **Hardware Connection:**
    - Connect the Bluetooth module and servo motors to the specified pins as described above.

2. **Bluetooth Device Pairing:**
    - Pair your Bluetooth device with the Bluetooth module.

3. **Sending Commands:**
    - Send commands in the format "X:valueY:value\n" to control servo positions.
    - For example, to set the position of the first servo (connected to pin 5), send "X:90Y:0\n".

## Note

- Adjust the baud rates and pins as needed based on your specific hardware setup.

## Sketch Information

### Libraries Used
- **ServoTimer2:**
    - Used to generate servo signals using Timer2.
- **SoftwareSerial:**
    - Enables communication with the Bluetooth module via software UART.

### Code Overview

1. **Bluetooth Connection Setup:**
    - SoftwareSerial is used to create a communication channel with the Bluetooth module.
    - The Bluetooth module is connected to pins 8 (RX) and 9 (TX).
    - Serial monitor and SoftwareSerial are initialized with a baud rate of 9600.

2. **Servo Initialization:**
    - An array of ServoTimer2 objects is created to control multiple servos.
    - Servos are attached to pins 5 and 6 (and can be extended up to 8 servos).

3. **Loop Function:**
    - Checks for available data from the Bluetooth module.
    - Reads the received data until a newline character is encountered.
    - Calls the `parseString` function to process the received data.
    - Updates the servo positions based on the extracted data.

4. **Parse String Function:**
    - Takes a string input as a parameter.
    - Searches for "X:" and "Y:" in the input string.
    - Extracts and parses the values following "X:" and "Y:".
    - Updates the servo positions with the extracted values.

### Author
- **Aleko khomasuridze**
- **Date: October 11, 2023**

### Additional Information
- The code is designed to control up to 8 servo motors. Adjust the buffer size and pin assignments if using a different number of servos or different pins.
- Ensure that your Bluetooth device is paired with the module and follows the specified command format for servo control.

Feel free to customize the code based on your specific requirements and hardware setup.

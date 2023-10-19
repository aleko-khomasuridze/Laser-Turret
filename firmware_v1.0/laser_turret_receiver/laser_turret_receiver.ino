/*
   Bluetooth Controlled Servo Motors

   This Arduino sketch demonstrates how to control servo motors using a Bluetooth module.
   It utilizes the ServoTimer2 library to overcome conflicts with the standard Servo library
   when using the SoftwareSerial library. The Bluetooth module communicates with the Arduino
   using SoftwareSerial, and servo signals are generated using Timer2.

   Hardware Configuration:
   - Bluetooth Module connected to pins 8 (RX) and 9 (TX)
   - Servo motors connected to pins 5 and 6 (you can extend up to 8 servos)
   
   Instructions:
   1. Connect the Bluetooth module and servo motors to the specified pins.
   2. Pair your Bluetooth device with the module.
   3. Send commands in the format "X:valueY:value\n" to control servo positions.

   Note: Adjust the baud rates and pins as needed based on your specific hardware setup.

   Written by: Aleko khomasuridze - Date: October 11, 2023
*/


// import required libraries 

// because standard Servo ans SoftwareSerial library both use Timer1 of atmega 
// it had some trouble with servo signals so i decided to use servo library that 
// used timer2 for generating correct signal and frequency fro my servos
#include <ServoTimer2.h>    
#include <SoftwareSerial.h>  // software UART libarary to communicate with BLUETOOTH

#define RX_REC 8  // BLUETOOTH RX PIN
#define TX_REC 9  // BLUETOOTH TX PIN

SoftwareSerial bluetooth(RX_REC, TX_REC); // Create a SoftwareSerial object for Bluetooth communication on pins 8 (RX) and 9 (TX)

void parseString(String inputString); // Function declaration for decoding received strings

#define bufferSize 2 // Define the size of the array to store extracted values

int dataArray[bufferSize]; // Create an array to store the extracted values

ServoTimer2 servo[bufferSize]; // Create an array of ServoTimer2 objects for controlling servos

void setup() {
  Serial.begin(9600); // Initialize the Serial monitor at a baud rate of 9600
  bluetooth.begin(9600); // Initialize the SoftwareSerial for Bluetooth at 9600 baud

  // Attach servos to pins 5 and 6 (ServoTimer2 library supports up to 8 servos)
  for (uint8_t i = 0; i < bufferSize; i++) {
    servo[i].attach(i + 5);
  }
}

void loop() {
  if (bluetooth.available()) { // Check if there's data available from the Bluetooth module
    String inputString = bluetooth.readStringUntil('\n'); // Read the Bluetooth data until a newline character is received
    parseString(inputString); // Call the parseString function to process the received data
  }
  
  // Update the servo positions based on the extracted dataArray values
  for (uint8_t i = 0; i < bufferSize; i++) {
    servo[i].write(dataArray[i]);
  }
}

void parseString(String inputString) {
  uint8_t startIndex = 0; // Initialize the start index for searching in the inputString
  
  // Find the position of "X:" and "Y:" in the received string
  int xPos = inputString.indexOf("X:");
  int yPos = inputString.indexOf("Y:");

  if (xPos != -1 && yPos != -1) {
    // Extract and parse integers following "X:" and "Y:"
    dataArray[0] = inputString.substring(xPos + 2, yPos).toInt(); // Extract and parse X
    dataArray[1] = inputString.substring(yPos + 2).toInt(); // Extract and parse Y

    // Now, you have the X and Y values in the dataArray
    // You can use them for further processing or output
    // For example, printing to serial monitor:
    // Serial.print("X: ");
    // Serial.print(dataArray[0]);
    // Serial.print(", Y: ");
    // Serial.println(dataArray[1]);
  }
}

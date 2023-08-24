// This sketch uses the hardware serial port for Bluetooth communication.

// Import the necessary libraries.
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Install in libraries pages

//MACROS are defined here
LiquidCrystal_I2C lcd16x2(0x27, 16, 2);

// Setup function runs once when the board is powered on.
void setup() {
  // Set the baud rate for the Bluetooth serial connection.
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(7, OUTPUT);

  lcd16x2.begin(16, 2, 1);
  lcd16x2.backlight();


  lcd16x2.print("Envision APP");
}

// Loop function runs repeatedly forever.
void loop() {
  // Check if there is any data available from the Bluetooth serial connection.
  if (Serial.available()) {
    // Read the data from the Bluetooth serial connection.
    String data = Serial.readString();

    // Print the data to the serial monitor.
    Serial.print(data + "\n");

    // Auto generated by PictoBlox
    if ((data == "sound play")) {
      tone(9, 440, 1000);
      delay(1000);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "light on")) {
      digitalWrite(7, true);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "light off")) {
      digitalWrite(7, false);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }
  }
}
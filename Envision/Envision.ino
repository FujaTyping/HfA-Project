// This sketch uses the hardware serial port for Bluetooth communication.

// Import the necessary libraries.
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // Install in libraries pages

//MACROS are defined here
LiquidCrystal_I2C lcd16x2(0x27, 16, 2);

// Setup function runs once when the board is powered on.
void setup() {
  // Set the baud rate for the Bluetooth serial connection.
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);

  lcd16x2.begin(16, 2, 1);
  lcd16x2.backlight();


  lcd16x2.print("Envision - HfA");
  lcd16x2.setCursor(1 - 1, 2 - 1);
  lcd16x2.print("V.0.1.2 BETA");
  Serial.print("Envision IDE\n");
  tone(9, 1760, 500);
  delay(500);
  tone(9, 1760, 500);
  delay(500);
}

// Loop function runs repeatedly forever.
void loop() {
  digitalWrite(10, true);

  if ((digitalRead(12) == 0)) {
    lcd16x2.clear();
    lcd16x2.print("Envision - HfA");
    lcd16x2.setCursor(1 - 1, 2 - 1);
    lcd16x2.print("V.0.1.2 BETA");
    Serial.print("Log : clear\n");
    tone(9, 1760, 500);
    delay(500);
  }

  // Check if there is any data available from the Bluetooth serial connection.
  if (Serial.available()) {
    // Read the data from the Bluetooth serial connection.
    String data = Serial.readString();

    // Print the data to the serial monitor.
    Serial.print("Data : " + data + "\n");

    // Auto generated by PictoBlox
    if ((data == "connected")) {
      digitalWrite(11, true);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Device :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print("connected");
    }

    if ((data == "disconnected")) {
      digitalWrite(11, false);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Device :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print("disconnected");
    }

    if ((data == "tone A2")) {
      tone(9, 110, 1000);
      delay(1000);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "tone A3")) {
      tone(9, 220, 1000);
      delay(1000);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "tone A4")) {
      tone(9, 440, 1000);
      delay(1000);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "tone A5")) {
      tone(9, 880, 1000);
      delay(1000);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "tone A6")) {
      tone(9, 1760, 1000);
      delay(1000);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "tone A7")) {
      tone(9, 3520, 1000);
      delay(1000);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "LED red")) {
      digitalWrite(6, true);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "LED blue")) {
      digitalWrite(5, true);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "LED green")) {
      digitalWrite(7, true);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "LED off")) {
      digitalWrite(7, false);
      digitalWrite(5, false);
      digitalWrite(6, false);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }
  }
  delay(100);
  digitalWrite(10, false);
  delay(100);
}
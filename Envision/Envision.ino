// This sketch uses the hardware serial port for Bluetooth communication.

// Import the necessary libraries.
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // Install in libraries pages
#include <LedControl.h>         // Install in libraries pages
#include <binary.h>

//MACROS are defined here
bool isConnect = false;
LedControl dotMatrixDisplay = LedControl(14, 16, 15, 1);
LiquidCrystal_I2C lcd16x2(0x27, 16, 2);

byte happy[8] = {
  0x3C,
  0x42,
  0x95,
  0xA1,
  0xA1,
  0x95,
  0x42,
  0x3C,
};

byte sad[8] = {
  0x3C,
  0x42,
  0xA5,
  0x91,
  0x91,
  0xA5,
  0x42,
  0x3C,
};

byte love[8] = {
  0x0C,
  0x1E,
  0x3E,
  0x7C,
  0x7C,
  0x3E,
  0x1E,
  0x0C,
};

byte circle[8] = {
  0x3C,
  0x7E,
  0xE7,
  0xC3,
  0xC3,
  0xE7,
  0x7E,
  0x3C,
};

byte squaree[8] = {
  0xFF,
  0xFF,
  0xC3,
  0xC3,
  0xC3,
  0xC3,
  0xFF,
  0xFF,
};

byte xx[8] = {
  0xC3,
  0xE7,
  0x7E,
  0x3C,
  0x3C,
  0x7E,
  0xE7,
  0xC3,
};

byte pacman[8] = {
  0x3C,
  0x7E,
  0xFF,
  0xFF,
  0xEB,
  0xE7,
  0x46,
  0x04,
};

byte house[8] = {
  0x08,
  0x0C,
  0xFE,
  0x9F,
  0x9F,
  0xFE,
  0x0C,
  0x08,
};

byte creaper[8] = {
  0x00,
  0x06,
  0x76,
  0x38,
  0x38,
  0x76,
  0x06,
  0x00,
};

float getDistance(int trig, int echo) {
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH) / 58.0;
}

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

  dotMatrixDisplay.shutdown(0, false);
  dotMatrixDisplay.setIntensity(0, 4);
  dotMatrixDisplay.clearDisplay(0);

  lcd16x2.print("Envision - HfA");
  lcd16x2.setCursor(1 - 1, 2 - 1);
  lcd16x2.print("V.0.1.4 BETA");
  Serial.print("Envision IDE\n");
  tone(9, 1760, 500);
  delay(500);
  tone(9, 1760, 500);
  delay(500);
}

// Loop function runs repeatedly forever.
void loop() {
  digitalWrite(10, true);

  Serial.print(String(getDistance(4, 3)) + " Cm\n");

  if ((digitalRead(12) == 0)) {
    if (isConnect) {
      digitalWrite(7, false);
      digitalWrite(5, false);
      digitalWrite(6, false);
      dotMatrixDisplay.clearDisplay(0);

      tone(9, 1760, 250);
      delay(250);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Envision - HfA");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print("V.0.1.4 BETA");
      // / LOG / // Serial.print("Log : reset\n");
    }
  }

  // Check if there is any data available from the Bluetooth serial connection.
  if (Serial.available()) {
    // Read the data from the Bluetooth serial connection.
    String data = Serial.readString();

    // Print the data to the serial monitor.
    // / LOG / // Serial.print("Data : " + data + "\n");

    // Auto generated by PictoBlox
    if ((data == "connected")) {
      digitalWrite(11, true);
      isConnect = true;

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Device :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print("connected");
    }

    if ((data == "disconnected")) {
      digitalWrite(11, false);
      isConnect = false;

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

    if ((data == "Matrix happy")) {
      printByte(happy);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "Matrix sad")) {
      printByte(sad);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "Matrix love")) {
      printByte(love);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "Matrix Circle")) {
      printByte(circle);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "Matrix Square")) {
      printByte(squaree);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "Matrix X")) {
      printByte(xx);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "Matrix Pac-Man")) {
      printByte(pacman);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "Matrix house")) {
      printByte(house);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "Matrix creeper")) {
      printByte(creaper);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }

    if ((data == "Matrix off")) {
      dotMatrixDisplay.clearDisplay(0);

      // Display lcd
      lcd16x2.clear();
      lcd16x2.print("Last command :");
      lcd16x2.setCursor(1 - 1, 2 - 1);
      lcd16x2.print(data);
    }
  }
  delay(250);
  digitalWrite(10, false);
  delay(250);
}

void printByte(byte character[]) {

  int i = 0;
  for (i = 0; i < 8; i++) {
    dotMatrixDisplay.setRow(0, i, character[i]);
  }
}
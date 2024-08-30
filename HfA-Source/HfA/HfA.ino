// Require Libray :
// Adafruit Unified Sensor
// DHT sensor library

#include "BluetoothSerial.h"
#include "DHT.h"

String DeviceName = "SmartHomevision";
String CMD = "";
String SerialByte = "";

#define DHTPIN 23
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BluetoothSerial SerialBT;

void setup() {
  pinMode(26, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(23, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin(DeviceName);
  Serial.println("[LOG] : Initialize complete");
}

void loop() {
  SerialByte = "";
  float Hum = dht.readHumidity();
  float Temp = dht.readTemperature();
  if (isnan(Hum) || isnan(Temp)) {
    SerialByte += "DHT 0 0";
  } else {
    SerialByte += "DHT " + String(Hum) + " " + String(Temp);
  }
  if (SerialBT.available() > 0) {
    CMD = SerialBT.readStringUntil('\n');
    Commands(CMD);
  }
  Serial.println("[SERIAL] : "+String(SerialByte));
  SerialBT.println(SerialByte);
  delay(1000);
}

void Commands(String CMD) {
  Serial.println("[CMD] : "+CMD);
  if(CMD == "LC") {
    digitalWrite(26, false);
  }
  if(CMD == "LO") {
    digitalWrite(26, true);
  }
  if(CMD == "LRO") {
    digitalWrite(18, true);
  }
  if(CMD == "LRF") {
    digitalWrite(18, false);
  }
  if(CMD == "LGO") {
    digitalWrite(19, true);
  }
  if(CMD == "LGF") {
    digitalWrite(19, false);
  }
  if(CMD == "LBO") {
    digitalWrite(23, true);
  }
  if(CMD == "LBF") {
    digitalWrite(23, false);
  }
}

int randint() {
  return random(0, 100);
}

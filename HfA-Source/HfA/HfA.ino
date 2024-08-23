// Require Libray :
// Adafruit Unified Sensor
// DHT sensor library

#include "BluetoothSerial.h"
#include "DHT.h"

String DeviceName = "SmartHomevision";
String CMD = "";
String SerialByte = "";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

#define DHTPIN 16
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(26, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(23, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin(DeviceName);
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
    Serial.println(CMD);
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
  SerialBT.println(SerialByte);
  delay(1000);
}

int randint() {
  return random(0, 100);
}

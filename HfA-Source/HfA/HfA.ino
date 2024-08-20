// Require Libray :
// Adafruit Unified Sensor
// DHT sensor library

#include "BluetoothSerial.h"
#include "DHT.h"

String device_name = "SmartHomevision";
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
  Serial.begin(115200);
  SerialBT.begin(device_name);
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
      Serial.println("Light OFF");
    }
    if(CMD == "LO") {
      Serial.println("Light ON");
    }
    if(CMD == "LRO") {
      Serial.println("RGB Red ON");
    }
    if(CMD == "LRF") {
      Serial.println("RGB Red OFF");
    }
    if(CMD == "LGO") {
      Serial.println("RGB Green ON");
    }
    if(CMD == "LGF") {
      Serial.println("RGB Green OFF");
    }
    if(CMD == "LBO") {
      Serial.println("RGB Blue ON");
    }
    if(CMD == "LBF") {
      Serial.println("RGB Blue OFF");
    }
  }
  SerialBT.println(SerialByte);
  delay(1000);
}

int randint() {
  return random(0, 100);
}
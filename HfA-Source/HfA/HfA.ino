#include "BluetoothSerial.h"

String device_name = "SmartHomevision";
String CMD = "";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);
}

void loop() {
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
  delay(50);
}

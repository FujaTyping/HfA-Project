// Require Libray :
// Adafruit Unified Sensor
// DHT sensor library
// EspSoftwareSerial
// DFRobotDFPlayerMini

#include "SoftwareSerial.h"
#include "BluetoothSerial.h"
#include "DHT.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t DFTXPIN = 26;
static const uint8_t DFRXPIN = 27;
String DeviceName = "SmartHomevision";
String CMD = "";
String SerialByte = "";
int DFVolume = 50;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

#define DHTPIN 16
#define DHTTYPE DHT11

SoftwareSerial softwareSerial(DFRXPIN, DFTXPIN);
DFRobotDFPlayerMini player;
DHT dht(DHTPIN, DHTTYPE);
BluetoothSerial SerialBT;

void setup() {
  pinMode(26, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(23, OUTPUT);
  Serial.begin(115200);
  softwareSerial.begin(115200);
  SerialBT.begin(DeviceName);
  if (player.begin(softwareSerial)) {
    Serial.println("[LOG] : DFPlayer connected");
    player.volume(DFVolume);
    //player.play(1);
    //player.playFolder(1, 1);
  } else {
    Serial.println("[LOG] : Can't connect to DFPlayer");
  }
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
    Serial.println("[CMD] : "+CMD);
    Commands(CMD);
  }
  SerialBT.println(SerialByte);
  delay(1000);
}

void Commands(String CMD) {
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
  if(CMD == "DFPLofi") {
    player.play(5);
  }
  if(CMD == "DFPRock") {
    player.play(3);
  }
  if(CMD == "DFPClassic") {
    player.play(4);
  }
  if(CMD == "DFPOrchestra") {
    player.play(2);
  }
  if(CMD == "DFPPop") {
    player.play(1);
  }
  if(CMD == "DFVU") {
    player.volumeUp();
  }
  if(CMD == "DFVD") {
    player.volumeDown();
  }
  if(CMD == "DFPU") {
    player.pause();
  }
}

int randint() {
  return random(0, 100);
}

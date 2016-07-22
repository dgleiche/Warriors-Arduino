#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
#include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE          0
#define MINIMUM_FIRMWARE_VERSION     "0.6.6"
#define MODE_LED_BEHAVIOR            "MODE"

//Bluefruit object using hardware SPI (SCK/MOSI/MISO)
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// A small error helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}


void setup() {
  //Wait for serial
  while (!Serial);
  delay(500);

  Serial.begin(115200);
  Serial.println(F("------------------------------------------+"));

  // Initialise the module
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if (!ble.begin(VERBOSE_MODE)) {
    error(F("Couldn't find Bluefruit, make sure it's in command mode & check wiring?"));
  }

  Serial.println(F("OK!"));
  Serial.println(F("------------------------------------------+"));
  Serial.println(F("Program now starting\n"));

  ble.verbose(false);

  // Wait for connection
  while (!ble.isConnected())
    delay(500);
}

void sendBLE(String data) {
  ble.print("AT+BLEUARTTX=");
  ble.println(data);
  ble.print("AT+BLEUARTTX=");
  ble.println(" \n");

  //Verify response
  if (!ble.waitForOK()) {
    Serial.println(F("Failed to send?"));
  }

  delay(100);
}

String receiveBLE() {
  bool done = false;
  String buffer = "";

  // Wait for data
  while (!done) {
    ble.println("AT+BLEUARTRX");
    ble.readline();

    if (strcmp(ble.buffer, "OK") == 0) {
      done = true;
    } else {
      buffer += String(ble.buffer);
    }
  }

  return buffer;
}

void loop() {
  String data = receiveBLE();
  if (data != "") Serial.println(data);
  delay(500);
  
}

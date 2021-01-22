//VERY IMPORTANT
//to see colors in terminals add this line at the end of platformio.ini
//monitor_flags = --raw
#include <Arduino.h>
#include "Colors.h"
#include "IoTicosSplitter.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>



void setup() {

  Serial.begin(921600);
  Serial.println("Hello World");

}

void loop() {
  // put your main code here, to run repeatedly:
}
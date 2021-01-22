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

String dId = "121212";
String webhook_pass = "SA7sxAKDVR";
String webhook_endpoint = "http://192.168.0.6:3001/api/getdevicecredentials";
const char* mqtt_server = "192.168.0.6";

//PINS 
#define led 2

//WiFi
const char *wifi_ssid = "GOLD2";
const char *wifi_password = "Tesla208";

//Functions definitions
bool get_mqtt_credentials();
void clear();

DynamicJsonDocument mqtt_data_doc(2048);

void setup() {

  Serial.begin(921600);
  pinMode(led, OUTPUT);
  clear();

  Serial.print(underlinePurple + "\n\n\nWiFi Connection in Progress" + fontReset + Purple);

  WiFi.begin(wifi_ssid,wifi_password);

  int counter = 0;

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    counter++;

    if(counter > 10){
      Serial.print("  ⤵" + fontReset);
      Serial.print(Red + "\n\n         Ups WiFi Connection Failed :( ");
      Serial.println(" -> Restarting..." + fontReset);
      delay(2000);
      ESP.restart();
    }
  }

  Serial.print("  ⤵" + fontReset);

  //Printing local ip
  Serial.println(boldGreen + "\n\n         WiFi Connection -> SUCCESS :)" + fontReset);
  Serial.print("\n         Local IP -> ");
  Serial.print(boldBlue);
  Serial.print(WiFi.localIP());
  Serial.println(fontReset);


  get_mqtt_credentials();


}

void loop() {

}



bool get_mqtt_credentials(){

  Serial.print(underlinePurple + "\n\n\nGetting MQTT Credentials from WebHook" + fontReset + Purple + "  ⤵");
  delay(1000);

  String toSend = "dId=" + dId + "&password=" + webhook_pass;

  HTTPClient http;
  http.begin(webhook_endpoint);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int response_code = http.POST(toSend);


  if(response_code < 0 ){
    Serial.print(boldRed + "\n\n         Error Sending Post Request :( " + fontReset);
    http.end();
    return false;
  }

  if(response_code != 200){
    Serial.print(boldRed + "\n\n         Error in response :(   e-> "  + fontReset + " " + response_code);
    http.end();
    return false;
  }

  if (response_code == 200){
    String responseBody = http.getString();

    Serial.print(boldGreen + "\n\n         Mqtt Credentials Obtained Successfully :) " + fontReset);
    
    deserializeJson(mqtt_data_doc, responseBody);
    http.end();
    delay(1000);
    

    //String mqtt_username = mqtt_data_doc["username"];
    //String mqtt_password = mqtt_data_doc["password"];
    //int freq  = mqtt_data_doc["variables"][1]["variableSendFreq"];
//
    //Serial.println(mqtt_username);
    //Serial.println(mqtt_password);
    //Serial.println(freq);

  }

  return false;

}


void clear()
{
  Serial.write(27);    // ESC command
  Serial.print("[2J"); // clear screen command
  Serial.write(27);
  Serial.print("[H"); // cursor to home command
}
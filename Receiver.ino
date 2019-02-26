
#include "orgb417pb.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

uint8_t GPIO_Pin = D2;

const char* ssid     = "UPC3499437";
const char* password = "wuNzAp3dhh7t";

const char* mqttServer = "cloud.hackcube.org";
const int mqttPort = 11883;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

ORGB417PB transciver(digitalPinToInterrupt(GPIO_Pin), D0);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char raw_message[30];
  for (int i = 0; i < length; i++) {
    raw_message[i] = (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();

//  // Switch on the LED if an 1 was received as first character
//  if ((char)payload[0] == '1') {
//    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//    // but actually the LED is on; this is because
//    // it is acive low on the ESP-01)
//  } else {
//    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//  }
  long ornoCode = atol(raw_message);
  Serial.println(ornoCode);
  transciver.send(ornoCode, 4);

}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
    }
  Serial.println("Connected to the WiFi network");
   
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  connectToMqtt();
 
  //client.publish("esp/test", "Hello from ESP8266");  
}

void connectToMqtt(){
    while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client")) {
 
      Serial.println("connected");  
      client.subscribe("socket");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}



void loop() {
  if(!client.connected()){
    connectToMqtt();
  }  
  client.loop();
  delay(1000);
  Serial.println("Działa");
//
//  if (transciver.has_code()) {
//    Serial.println(transciver.code());
//    transciver.clear_code();
//  }
//
//  transciver.send(16266309, 4);
//  delay(1000);
//
//  if (transciver.has_code()) {
//    Serial.println(transciver.code());
//    transciver.clear_code();
//  }
}



/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/


// Replace with your network credentials
//const char* ssid = "Telia-3E632D";
//const char* password = "B79D32679B";
const char* ssid = "Salvar";
const char* password = "Swordfish";


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String getDistance() {
  //Write random value for testing - placeholders
  String distance_string = String(random(50))+","+String(random(50));
  Serial.println(distance_string);
  return(distance_string);
}


void setup(){
  Serial.begin(115200);
  
  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getDistance().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}

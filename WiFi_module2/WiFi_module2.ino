
#include <WiFi.h>
#include <ESPAsyncWebServer.h>


// 2.4Ghz WiFi
// Set SSID and password
const char* ssid = "PCC_IPS";
const char* password = "Rincewind";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String distance() {
  // Random variable for testing, will be actual distance
  return String(random(30));
}


void initWiFi() {
  
  Serial.print("Setting AP (Access Point)…");
  
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.on("", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", distance().c_str());
  });
  
  // Start server
  server.begin();
}


void setup() {
  Serial.begin(115200);
  initWiFi();
}

void loop() {
}

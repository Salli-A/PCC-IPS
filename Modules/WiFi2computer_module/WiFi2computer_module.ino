
#include <WiFi.h>
#include <ESPAsyncWebServer.h>


// 2.4Ghz WiFi
// Set SSID and password
const char* ssid = "PCC-IPS";
const char* password = "swordfish";
const char* host = "192.168.1.195";

// Set web server port number to 80
AsyncWebServer server(80);

// Variable to store the HTTP request
String header;


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
unsigned long previousMillis = 0;
unsigned long interval = 30500;
volatile float distance = 0;

String dist() {
  distance = random(25);
  return String(distance);
}

void wifi_down() {
  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}

void initWiFi() {
  
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  Serial.println(WiFi.localIP());

  server.on("", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", dist().c_str());
  });

  bool status;
  
  server.begin();
}


void setup() {
  Serial.begin(115200);
  initWiFi();
}


void loop() {

  // Listen for incoming clients
  //WiFiClient client = server.available();

  // If a new client
  //if (client) {
  //  distance = dist();
  //  client.print(String(distance));
  //}

  //send(distance, "text/plain", 2);

  //delay(500);

  // Check if if WiFi is down, try reconnecting
  wifi_down();
}

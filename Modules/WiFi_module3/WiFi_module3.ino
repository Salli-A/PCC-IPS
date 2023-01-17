
#include <WiFi.h>
#include <ESPAsyncWebServer.h>


// 2.4Ghz WiFi
// Set SSID and password

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

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
  server.begin();
}


void setup() {
  Serial.begin(115200);
  initWiFi();
}

unsigned long previousMillis = 0;
unsigned long interval = 30000;
volatile float distance = 0; 

int getDist() {
  distance = random(25); 
  return distance;
}

void loop() {
  // Generate random number
  distance = random(25); 
  
  // Listen for incoming clients
  WiFiClient client = server.available();

  // If a new client
  //while (client) {
  //  client.print(String(distance));
  //  distance = getDist();
  //}

  send(distance, "text/plain", 2);
    
  // Check if if WiFi is down, try reconnecting
  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}

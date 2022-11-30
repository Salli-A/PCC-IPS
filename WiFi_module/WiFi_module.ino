
#include <WiFi.h>
#include <ESPAsyncWebServer.h>


// 2.4Ghz WiFi
// Set SSID and password
const char* ssid = "Telia-3E632D";
const char* password = "B79D32679B";

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

void loop() {
  // Generate random number
  distance = random(25); 
  
  // Listen for incoming clients
  WiFiClient client = server.available();
  
  // If a new client connects,
  if (client) {
    // Display the HTML web page
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    
    // Web Page Heading
    client.println("<body><h1>ESP32 Web Server</h1>");
            
    client.println("<p>");
    client.print(" Distance from Anchor: ");
    client.print(String(distance));
    client.print(" [m]");
    client.println("<\p>");
    
  }
    
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

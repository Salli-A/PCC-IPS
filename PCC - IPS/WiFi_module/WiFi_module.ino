
#include <WiFi.h>



// 2.4Ghz WiFi
const char* ssid = "";
const char* password = "";

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
    currentTime = millis();
    previousTime = currentTime;
    
    // print a message out in the serial port
    Serial.println("New Client.");
    
    // make a String to hold incoming data from the client
    String currentLine = "";
    
    // loop while the client's connected
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      // if there's bytes to read from the client,
      if (client.available()){
        // read a byte, then
        char c = client.read();
        // print it out the serial monitor
        Serial.write(c);
        header += c;
        // if the byte is a newline character
        if (c == '\n') {
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
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
            // If the output26State is off, it displays the ON button
            
        }
      }
    }
    // Clear the header variable
    //header = "";
    // Close the connection
    //client.stop();
    //Serial.println("Client disconnected.");
    //Serial.println("");
      }
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

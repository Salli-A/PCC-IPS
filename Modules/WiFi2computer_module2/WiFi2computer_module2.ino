
#include <WiFi.h>
#include <ESPAsyncWebServer.h>


// 2.4Ghz WiFi
// Set SSID and password
const char* ssid = "PCC-IPS";
const char* password = "swordfish";
const char* host = "192.168.1.195";

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
  distance = random(69);
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

void send_udp(String *msg_json)
{
  if (client.connected())
  {
    client.print(*msg_json);
    Serial.println("UDP send");
  }
}


void init_wiFi() {

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());

  if (client.connect(host, 80))
  {
    Serial.println("Success");
    client.print(String("GET /") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n");
  }
}


void setup() {
  Serial.begin(115200);
  init_wiFi();
}


void loop() {
  delay(500);

  make_link_json(uwb_data, &all_json);
  send_udp(&all_json);
  runtime = millis();

  wifi_down();
}

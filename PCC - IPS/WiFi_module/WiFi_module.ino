
#include <WiFi.h>



// 2.4Ghz WiFi
const char* ssid = "";
const char* password = "";

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(115200);
  initWiFi();
}

unsigned long previousMillis = 0;
unsigned long interval = 30000;

void loop() {

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

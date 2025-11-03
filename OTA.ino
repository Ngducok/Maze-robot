#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "UEH-MEKONG"; // tên Wi-Fi 
const char* password = "";      // Wi-Fi mở thì để chuỗi rỗng

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
}

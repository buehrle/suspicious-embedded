#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//#include "core/suspicious.h"

const char SSID[] = "MIB";
const char PSK[] = "97654321";

WiFiClient client;

void connectWiFi();

void setup() {
  Serial.begin(9600);
  connectWiFi();
}

void loop() {

}

void connectWiFi() {
  WiFi.mode(WIFI_STA); //Station (client)
  WiFi.begin(SSID, PSK);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting connection...\r\n");
    delay(1000);
  }

  Serial.print("Connected.\r\n");
}

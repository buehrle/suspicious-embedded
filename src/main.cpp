#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//#include "core/suspicious.h"

const char SSID[] = "ipfire@buehrle";
const char PSK[] = "FFG5RT6890OP";

WiFiClient client;

void connectWiFi();

void setup() {
  Serial.begin(9600);
  connectWiFi();

  if (client.connect("www.google.com", 80) ) {
    Serial.print("Yee.");
  }
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

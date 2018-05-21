#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "modules/esp8266/esp8266.h"
#include "core/suspicious.h"

char SSID[] = "Gast";
char PSK[] = "";

void setup() {
  Suspicious::init("127.0.0.1", "Flo's Testdevice", "0", 2, true);
  Suspicious::connectWiFi(SSID, PSK, 10000);

  char* lello;

  module_sendJSON("http://192.168.50.101:80", "LEL", lello);
}

void loop() {

}

#include "esp8266.h"

void module_init() {
  if (module_debug) {
    Serial.begin(9600);

    Serial.print("Initializing module...\r\n");
  }

  EEPROM.begin(64);

  if (module_debug) {
    Serial.print("Finished initializing module.\r\n");
  }
}

void module_saveToken(char* token) {
  for (int i = 0; i < 64; i++) {
    EEPROM.write(i, token[i]);
  }

  EEPROM.commit();
}

char* module_getSavedToken() {
  char* token = new char[64];

  for (uint i = 0; i < 64; i++) {
    token[i] = EEPROM.read(i);
  }
  
  return token;
}

char* module_sendData(char uri[], char data[]) {
  return new char[0];
}

s_wlan_connection_status module_connectWiFi(char* ssid, char* psk, int timeout) {
  if (module_debug) {
    Serial.print("Attempting WiFi-connection...\r\n");
  }

  WiFi.mode(WIFI_STA); //Station (client)
  WiFi.begin(ssid, psk);

  int timeoutcount = 0;

  while (timeoutcount <= timeout) {
    if (WiFi.status() == WL_CONNECTED) {
      if (module_debug) {
        Serial.print("Successfully established a WiFi-connection.\r\n");
      }

      return SUCCESSFUL;
    }

    delay(10);
    timeoutcount += 10;
  }

  if (module_debug) {
    Serial.print("Failed to establish a WiFi-connection.\r\n");
  }

  return FAILED;
}

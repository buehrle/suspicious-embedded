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
  for (int i = 1; i < 65; i++) {
    EEPROM.write(i, token[i]);
  }

  EEPROM.write(0, 111);

  EEPROM.commit();
}

bool module_tokenPresent() {
  return (EEPROM.read(0) == 111);
}

char* module_getSavedToken() {
  char* token = new char[64];

  for (int i = 1; i < 65; i++) {
    token[i] = EEPROM.read(i);
  }

  return token;
}

s_request_status module_sendJSON(char* host, int port, const char* uri, char* data, char* &response) {
  if (module_debug) {
    Serial.print("Sending HTTP request...\r\n");
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient httpclient;

    httpclient.begin(host, port, uri, false, "");
    httpclient.addHeader("Content-Type", "text/json");

    int httpcode = httpclient.POST(data);

    if (httpcode != 200) {
      httpclient.end();

      if (module_debug) {
        Serial.print("HTTP error occured.\r\n");
      }

      return HTTP_ERROR;
    }

    String _response = httpclient.getString();
    response = new char[_response.length() + 1];
    strcpy(response, _response.c_str());

    httpclient.end();

    if (module_debug) {
      Serial.print("HTTP request successful.\r\n");
    }

    return HTTP_SUCCESSFUL;
  } else {
    return CONNECTION_LOST;
  }
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

  WiFi.disconnect();

  if (module_debug) {
    Serial.print("Failed to establish a WiFi-connection.\r\n");
  }

  return FAILED;
}

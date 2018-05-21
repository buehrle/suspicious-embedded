#ifndef WIFI_
#define WIFI_

enum s_wlan_connection_status {
  SUCCESSFUL,
  FAILED
};

s_wlan_connection_status module_connectWiFi(char* ssid, char* psk, int timeout);

#endif

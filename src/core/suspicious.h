#ifndef SUSPICIOUS_
#define SUSPICIOUS_

#include "units.h"
#include "sensor.h"
#include "../modules/module.h"
#include "../modules/esp8266/esp8266.h"

enum s_wlan_connection_status {
  SUCCESSFUL,
  FAILED
};

enum s_init_status {
  TOKEN_REQUESTED,
  TOKEN_PRESENT,
  ERROR
};

class Suspicious {
public:
  Suspicious(char* server, char* devicename, char* userid, int sensorcount);
  static s_wlan_connection_status connectWiFi(char* ssid, char* psk, int timeout);
  void registerSensor(char* sensorname, int internalid, char* unit, int defaultupdatefreq, int minupdatefreq, int maxupdatefreq);
  s_init_status init();
  bool tokenValidated();
  void updateSensor(char* sensorname, char* unit, char* value);
  void updateSensor(int internalid, char* unit, char* value);
private:
  void _updateSensor(int index, char* unit, char* value);
  char **server;
  char **devicename;
  char **userid;
  char *token;
  int registeredsensors;
  SENSOR *sensors;
};

#endif

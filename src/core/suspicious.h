#ifndef SUSPICIOUS_
#define SUSPICIOUS_

#include "units.h"
#include "sensor.h"
#include "../modules/module.h"
#include "../modules/wifi.h"

enum s_startup_status {
  TOKEN_REQUESTED,
  TOKEN_PRESENT,
  ERROR
};

class Suspicious {
public:
  static void init(char* server, char* devicename, char* registrationtoken, int sensorcount, bool debug);
  static s_wlan_connection_status connectWiFi(char* ssid, char* psk, int timeout);
  static void registerSensor(char* sensorname, int internalid, char* unit, int defaultupdatefreq, int minupdatefreq, int maxupdatefreq);
  static s_startup_status startup();
  static bool tokenValidated();
  static void updateSensor(char* sensorname, char* unit, char* value);
  static void updateSensor(int internalid, char* unit, char* value);
private:
  Suspicious() {};
  static void _updateSensor(int index, char* unit, char* value);
  static char* server;
  static char* devicename;
  static char* registrationtoken;
  static char* token;
  static int registeredsensors;
  static SENSOR* sensors;
};

#endif

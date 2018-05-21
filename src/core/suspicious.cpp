#include "suspicious.h"

#ifdef MODULE_EXISTS

char** Suspicious::server;
char** Suspicious::devicename;
char** Suspicious::userid;
char* Suspicious::token;
int Suspicious::registeredsensors;
SENSOR* Suspicious::sensors;

void Suspicious::begin(char* server, char* devicename, char* userid, int sensorcount) {
  Suspicious::server = &server;
  Suspicious::devicename = &devicename;
  Suspicious::userid = &userid;
  Suspicious::registeredsensors = 0;
  Suspicious::sensors = new SENSOR[sensorcount];
}

s_wlan_connection_status Suspicious::connectWiFi(char* ssid, char* psk, int timeout) {

}

void Suspicious::registerSensor(char* sensorname, int internalid, char* unit, int defaultupdatefreq, int minupdatefreq, int maxupdatefreq) {
  SENSOR newsensor;
  newsensor.sensorname = sensorname;
  newsensor.internalid = internalid;
  newsensor.unit = unit;
  newsensor.defaultupdatefreq = defaultupdatefreq;
  newsensor.minupdatefreq = minupdatefreq;
  newsensor.maxupdatefreq = maxupdatefreq;

  Suspicious::sensors[Suspicious::registeredsensors] = newsensor;
  Suspicious::registeredsensors++;
}

s_startup_status Suspicious::startup() {
  module_init();

  if (Suspicious::token = module_getSavedToken()) {
    return TOKEN_PRESENT;
  } else {
    //TODO request token
    return TOKEN_REQUESTED;
  }
}

bool Suspicious::tokenValidated() {
  //TODO Some magic with module_sendData
  //Request to the REST service and check if saved token is validated
  return true;
}

void Suspicious::updateSensor(char* sensorname, char* unit, char* value) {
  for (int i = 0; i < Suspicious::registeredsensors - 1; i++) {
    if (Suspicious::sensors[i].sensorname == sensorname) {
      Suspicious::_updateSensor(i, unit, value);
    }
  }
}

void Suspicious::updateSensor(int internalid, char* unit, char* value) {
  for (int i = 0; i < Suspicious::registeredsensors - 1; i++) {
    if (Suspicious::sensors[i].internalid == internalid) {
      Suspicious::_updateSensor(i, unit, value);
    }
  }
}

void Suspicious::_updateSensor(int index, char* unit, char* value) {

}

#else
#error "You have to specify a module!"
#endif

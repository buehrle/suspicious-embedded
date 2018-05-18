#include "suspicious.h"

#ifdef MODULE_EXISTS

Suspicious::Suspicious(char server[], char devicename[], char userid[], int sensorcount) {
  Suspicious::server = &server;
  Suspicious::devicename = &devicename;
  Suspicious::userid = &userid;
  Suspicious::registeredsensors = 0;
  Suspicious::sensors = new SENSOR[sensorcount];
}

void Suspicious::registerSensor(char sensorname[], int internalid, char unit[], int defaultupdatefreq, int minupdatefreq, int maxupdatefreq) {
  SENSOR newsensor;
  newsensor.sensorname = &sensorname;
  newsensor.internalid = &internalid;
  newsensor.unit = &unit;
  newsensor.defaultupdatefreq = &defaultupdatefreq;
  newsensor.minupdatefreq = &minupdatefreq;
  newsensor.maxupdatefreq = &maxupdatefreq;

  Suspicious::sensors[Suspicious::registeredsensors] = newsensor;
  Suspicious::registeredsensors++;
}

void Suspicious::init() {
  module_init();

  //if (Suspicious::token = module_getSavedToken == nullptr) {
    //Json::Value root;

    //TODO: Some magic with module_sendData
    //Suspicious::token = get new token
  //}
}

bool Suspicious::tokenValidated() {
  //TODO Some magic with module_sendData
  //Request to the REST service and check if saved token is validated
  return true;
}

#else
#error "You have to specify a module!"
#endif

#include "suspicious.h"

#ifdef MODULE_EXISTS

Suspicious::Suspicious(char server[], char devicename[], char userid[], int sensorcount) {
  this->server = &server;
  this->devicename = &devicename;
  this->userid = &userid;
  this->registeredsensors = 0;
  this->sensors = new SENSOR[sensorcount];
}

void Suspicious::registerSensor(char sensorname[], int internalid, char unit[], int defaultupdatefreq, int minupdatefreq, int maxupdatefreq) {
  SENSOR newsensor;
  newsensor.sensorname = &sensorname;
  newsensor.internalid = &internalid;
  newsensor.unit = &unit;
  newsensor.defaultupdatefreq = &defaultupdatefreq;
  newsensor.minupdatefreq = &minupdatefreq;
  newsensor.maxupdatefreq = &maxupdatefreq;

  this->sensors[this->registeredsensors] = newsensor;
  this->registeredsensors++;
}

void Suspicious::init() {
  module_init();

  if (this->token = module_getSavedToken()) {


    //TODO: Some magic with module_sendData

  } else {
    //TODO
  }
}

bool Suspicious::tokenValidated() {
  //TODO Some magic with module_sendData
  //Request to the REST service and check if saved token is validated
  return true;
}

void Suspicious::updateSensor(char sensorname[], char unit[], char value[]) {
  for (int i = 0; i < this->registeredsensors - 1; i++) {
    if (*this->sensors[i].sensorname == sensorname) {
      this->_updateSensor(i, unit, value);
    }
  }
}

void Suspicious::updateSensor(int internalid, char unit[], char value[]) {
  for (int i = 0; i < this->registeredsensors - 1; i++) {
    if (*this->sensors[i].internalid == internalid) {
      this->_updateSensor(i, unit, value);
    }
  }
}

void Suspicious::_updateSensor(int index, char *unit, char *value) {

}

#else
#error "You have to specify a module!"
#endif

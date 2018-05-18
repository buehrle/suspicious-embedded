#ifndef SUSPICIOUS_
#define SUSPICIOUS_

#include "units.h"
#include "sensor.h"
#include "../modules/module.h"
#include "../modules/esp8266/esp8266.h"

using namespace std;

class Suspicious {
public:
  Suspicious(char server[], char devicename[], char userid[], int sensorcount);
  void registerSensor(char sensorname[], int internalid, char unit[], int defaultupdatefreq, int minupdatefreq, int maxupdatefreq);
  void init();
  bool tokenValidated();
  void updateSensor(char sensorname[], char unit[], char value[]);
  void updateSensor(int internalid, char unit[], char value[]);
private:
  char **server;
  char **devicename;
  char **userid;
  char **token;
  int registeredsensors;
  SENSOR *sensors;
};

#endif

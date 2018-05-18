#ifndef SENSOR_
#define SENSOR_

using namespace std;

struct SENSOR {
  char **sensorname;
  int* internalid;
  char **unit;
  int* defaultupdatefreq;
  int *minupdatefreq;
  int *maxupdatefreq;
};

#endif

#include "suspicious.h"

char* Suspicious::server;
char* Suspicious::devicename;
char* Suspicious::registrationtoken;
char* Suspicious::token;
int Suspicious::registeredsensors;
SENSOR* Suspicious::sensors;

bool module_debug = true;

void Suspicious::init(char* server, char* devicename, char* registrationtoken, int sensorcount, bool debug) {
  Suspicious::server = server;
  Suspicious::devicename = devicename;
  Suspicious::registrationtoken = registrationtoken;
  Suspicious::registeredsensors = 0;
  Suspicious::sensors = new SENSOR[sensorcount];
  module_debug = debug;

  module_init();
}

s_wlan_connection_status Suspicious::connectWiFi(char* ssid, char* psk, int timeout) {
  return module_connectWiFi(ssid, psk, timeout);
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
  if (module_tokenPresent()) {
    Suspicious::token = module_getSavedToken();
    return STARTUP_TOKEN_PRESENT;
  } else {
    DynamicJsonBuffer buffer;

    JsonObject& out_root = buffer.createObject();
    out_root["name"] = Suspicious::devicename;
    out_root["deviceRegistrationToken"] = Suspicious::registrationtoken;

    JsonArray& out_sensors = out_root.createNestedArray("sensors");

    for (int i = 0; i < Suspicious::registeredsensors; i++) {
      JsonObject& out_sensor = out_sensors.createNestedObject();
      out_sensor["name"] = Suspicious::sensors[i].sensorname;
      out_sensor["internalID"] = Suspicious::sensors[i].internalid;
      out_sensor["unit"] = Suspicious::sensors[i].unit;
      out_sensor["defaultUpdateFrequency"] = Suspicious::sensors[i].defaultupdatefreq;
      out_sensor["minUpdateFrequency"] = Suspicious::sensors[i].minupdatefreq;
      out_sensor["maxUpdateFrequency"] = Suspicious::sensors[i].maxupdatefreq;
    }

    char* requeststring;
    char* responsestring;

    out_root.printTo(requeststring);

    delete [] &out_root;
    delete [] &out_sensors;

    buffer.clear();

    s_request_status status = module_sendJSON(Suspicious::server, 80, ROUTE_DEVICE_REGISTRATION, requeststring, responsestring);

    if (status == CONNECTION_LOST) return STARTUP_CONNECTION_LOST;
    if (status == HTTP_ERROR) return STARTUP_ERROR;

    JsonObject& in_root = buffer.parseObject(responsestring);

    char* token = in_root["token"];
    Suspicious::token = token;
    module_saveToken(token);

    return STARTUP_TOKEN_REQUESTED;
  }
}

bool Suspicious::tokenValidated() {
  //TODO Some magic with module_sendJSON
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

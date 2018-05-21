#ifndef MODULE_
#define MODULE_

extern bool module_debug;

enum s_request_status {
  HTTP_SUCCESSFUL,
  CONNECTION_LOST,
  HTTP_ERROR
};

void module_init();
void module_saveToken(char* token);
bool module_tokenPresent();
char* module_getSavedToken();
s_request_status module_sendJSON(char* host, int port, const char* uri, char* data, char* &response);

#endif

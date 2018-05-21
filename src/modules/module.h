#ifndef MODULE_
#define MODULE_

extern bool module_debug;

void module_init();
void module_saveToken(char* token);
char* module_getSavedToken();
char* module_sendData(char uri[], char data[]);

#endif

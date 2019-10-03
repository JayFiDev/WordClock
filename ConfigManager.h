#ifndef CONFIGMANAGER_H // include guard
#define CONFIGMANAGER_H

#include <EEPROM.h>
#include <ESP8266WebServer.h>

class ConfigManager
{

public:

    ConfigManager();
    void update();

private:

    ESP8266WebServer* server;
    void handle_root();
    void handle_msg();

    int eepromAddress = 0;
    struct eeprom_settings {
        int utc_offset = 1;
    } s;

    void getSettings();
    void setSettings();


};


#endif /* CONFIGMANAGER_H */
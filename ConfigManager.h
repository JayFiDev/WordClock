#ifndef CONFIGMANAGER_H // include guard
#define CONFIGMANAGER_H

#include <EEPROM.h>
#include <ESP8266WebServer.h>

class ConfigManager
{

public:

    ConfigManager();
    void update();
    int timeOffsetHourInSeconds();

private:

    const String form =
  "<p>"
  "<center>"
  "<h1>WordClock Configuration</h1>"
  "<h2>time zone settings</h2>"
  "<form action='utc'><p>Enter offset to utc: <input type='text' name='utc' size=30 autofocus> <input type='submit' value='Submit'></form>"
  "<h2>other settings</h2>"
  "<form action='msg'><p>Other: <input type='text' name='msg' size=30 autofocus> <input type='submit' value='Submit'></form>"
  "</center>";


    ESP8266WebServer* server;
    void handle_root();
    void handle_utc();
    void handle_other();

    int eepromAddress = 0;
    struct eeprom_settings {
        int utc_offset = 1;
    } s;

    void getSettings();
    void setSettings();


};


#endif /* CONFIGMANAGER_H */
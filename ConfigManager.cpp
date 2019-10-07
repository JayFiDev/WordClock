#include "ConfigManager.h"

ConfigManager::ConfigManager(){
    EEPROM.begin(512);
    getSettings();

    server = new ESP8266WebServer(80);
    server->on("/", std::bind(&ConfigManager::handle_root, this));
    server->on("/utc", std::bind(&ConfigManager::handle_utc, this));
    server->on("/msg", std::bind(&ConfigManager::handle_other, this));
    server->begin();
}

void ConfigManager::update(){
    server->handleClient();
}

int ConfigManager::timeOffsetHourInSeconds()
{
    return s.utc_offset*3600;
}

void ConfigManager::getSettings(){
    EEPROM.get(eepromAddress, s);
    Serial.println(s.utc_offset);
}

void ConfigManager::setSettings(){
    EEPROM.put(eepromAddress, s);
    EEPROM.commit();
}

void ConfigManager::handle_root()
{

  String form_temp = form;
  server->send(200, "text/html", form_temp);
}

void ConfigManager::handle_utc() 
{
  
  String form_temp = form;
  server->send(200, "text/html", form_temp);                    // Send same page so they can send another msg

  String msg = server->arg("utc");
  int offset = msg.toInt();
  if(offset > -12 && offset < 12)
  {
    Serial.print("Setting utc offset to EEPROM = ");
    Serial.println(offset);
    s.utc_offset = offset;
    setSettings();
  }
}

void ConfigManager::handle_other() 
{
  
  String form_temp = form;
  server->send(200, "text/html", form_temp);                    // Send same page so they can send another msg

  String msg = server->arg("msg");
  Serial.println(msg);

}
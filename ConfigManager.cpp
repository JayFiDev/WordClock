#include "ConfigManager.h"

ConfigManager::ConfigManager(){
    getSettings();
    server = new ESP8266WebServer(80);
    
    server->on("/", std::bind(&ConfigManager::handle_root, this));
    server->on("/msg", std::bind(&ConfigManager::handle_msg, this));
    server->begin();
}

void ConfigManager::update(){
    server->handleClient();
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

  String form_temp = "Hello, world!";
  
 
  
  server->send(200, "text/html", form_temp);
}

void ConfigManager::handle_msg() 
{
  
  String form_temp = "Hello, world!";
  
  server->send(200, "text/html", form_temp);                    // Send same page so they can send another msg

  String msg = server->arg("msg");
  Serial.println(msg);

  
//   if(msg == "Alarm1On"){
//     Serial.println("Alarm1 is now on");
//     s.alarm1 = true;

//   }else if(msg == "Alarm1Off"){
//     Serial.println("Alarm1 is now off");
//     s.alarm1 = false;
//     mp3_stop();

//   }
//   else if(msg.startsWith("AlarmTime1")){
//     Serial.println("AlarmTime1");
//     String newHour = msg.substring(11,13);
//     String newMin = msg.substring(14,17);
// //    Serial.print("hour: ");
// //    Serial.println(newHour);
//     s.alarm_hour1 = newHour.toInt();
// //    Serial.print("min: ");
// //    Serial.println(newMin);
//     s.alarm_min1 = newMin.toInt();

//     Serial.print("New Alarm1 is: ");
//     Serial.print(s.alarm_hour1);
//     Serial.print(":");
//     Serial.println(s.alarm_min1);
//   }
//   else if(msg == "Alarm2On"){
//     Serial.println("Alarm2 is now on");
//     s.alarm2 = true;
//   }
//   else if(msg == "Alarm2Off"){
//     Serial.println("Alarm2 is now off");
//     s.alarm2 = false;
    
//   }
//   else if(msg.startsWith("AlarmTime2")){
//     Serial.println("AlarmTime2");
//     String newHour = msg.substring(11,13);
//     String newMin = msg.substring(14,17);
// //    Serial.print("hour: ");
// //    Serial.println(newHour);
//     s.alarm_hour2 = newHour.toInt();
// //    Serial.print("min: ");
// //    Serial.println(newMin);
//     s.alarm_min2 = newMin.toInt();

//     Serial.print("New Alarm2 is: ");
//     Serial.print(s.alarm_hour2);
//     Serial.print(":");
//     Serial.println(s.alarm_min2);
  
//   }
//   else if(msg.startsWith("Music")){
//     Serial.println("Music");
//     String songNr = msg.substring(5,6);
//     Serial.println(songNr);
    
//     mp3_play(songNr.toInt());
//   }
//   else if(msg.startsWith("Led")){
//     Serial.println("Led");
//     String led = msg.substring(3,5);
//     Serial.println(led);
    
//     wakeUpLedMeter(led.toInt());
//   }
//   else if(msg.startsWith("summer") || msg.startsWith("sommer")){
//     s.summertime = true;
//     getNTPTime();
//   }
//   else if(msg.startsWith("winter")){
//     s.summertime = false;
//     getNTPTime();
//   }
  

}
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiManager.h>    
#include <NTPClient.h>
#include <TimeLib.h>

#include "DisplayManager.h" //matrix display
#include "ConfigManager.h" //webserver for configuration

#define RESET_PIN D2
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

ConfigManager* config;
DisplayManager* display;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(RESET_PIN, INPUT_PULLUP);
  int is_pressed = digitalRead(RESET_PIN);
  bool reset_pressed = false;

  if( is_pressed == 0){
    Serial.println("Reset pressed");
    reset_pressed = true;
  }
  
  startup_wifi_manager(reset_pressed);

  timeClient.begin();

  config = new ConfigManager();
  display = new DisplayManager();
}

void loop() {

  config->update();
  display->update();
  
  get_ntp_time();
  delay(1000);
}


//Wifi Manger
//setup wifi for ntp connection to get current time without rtc
void startup_wifi_manager(bool reset){
    WiFiManager wifiManager;
    wifiManager.setConfigPortalTimeout(300); //wait 300 seconds -> then return no matter if configured or not...
    
    //reset saved settings
    if(reset){
      wifiManager.resetSettings();
    }
    
      
    //set custom ip for portal
    wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    wifiManager.autoConnect("WordClock");
}

//NTP Client
void get_ntp_time(){

  timeClient.setTimeOffset(config->timeOffsetHourInSeconds());
  timeClient.update();  

  //set current internal time to ntp time
  setTime(timeClient.getEpochTime());


  //Serial.println(timeClient.getFormattedTime());
  //Serial.println(timeClient.getEpochTime());
  
}



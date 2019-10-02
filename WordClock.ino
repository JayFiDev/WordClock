#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>    
#include <NTPClient.h>
  
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  startup_wifi_manager();

  timeClient.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  get_ntp_time();
  delay(3000);
}


//Wifi Manger
//setup wifi for ntp connection to get current time without rtc
void startup_wifi_manager(){
    WiFiManager wifiManager;
    //wifiManager.setConfigPortalTimeout(300); //wait 300 seconds -> then return no matter if configured or not...
    
    //reset saved settings
    //wifiManager.resetSettings();
      
    //set custom ip for portal
    wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    wifiManager.autoConnect("WordClock");
}

//NTP Client
void get_ntp_time(){
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  
}

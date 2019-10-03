# WordClock

## Hardware
- 3d printed case
- (optional) lasered metal frontplate
- ESP8266 Board
- (optional) RTC
- 8x8 Neopixel matrix
- (optional) Buttons

## 3D Model
- Initial setup is done
- [ ] improve printability
- [ ] add rounded corners
- [ ] add buttons cutouts
- [ ] new frontplate export

## Software 

### WifiManager - initial configuration
- [x] Implemented
- [x] custom ip, ssid

### NTP client
- [x] Implemented

### WebServer - configuration of timezone, other options
- [x] Implemented initial version
- [x] functions to set, save, read from eeprom for config data
- [ ] how to get ip adress? -> serial atm.
- [ ] matrix options (different modes, etc)
- [ ] set time from web interface

### RTC
- [ ] save ntp to rtc
- [ ] code for reading/writing to rtc

### RGB matrix
- [x] layout
- [ ] code to display time
- [ ] mapping time to pixels
- [ ] different color modes


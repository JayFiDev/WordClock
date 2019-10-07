#ifndef DISPLAYMANAGER_H // include guard
#define DISPLAYMANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>

/*
    The following code is heavily inspired by Adafruits WordClock - Thank you!!

    Adafruit: https://learn.adafruit.com/neomatrix-8x8-word-clock)

    A T W E N T Y D
    Q U A R T E R Y
    F I V E H A L F
    D P A S T O R O
    F I V E I G H T
    S I X T H R E E
    T W E L E V E N
    F O U R N I N E

 */

#define DAYBRIGHTNESS 20
#define NIGHTBRIGHTNESS 10
#define MORNINGCUTOFF 5  // when does daybrightness begin?   7am
#define NIGHTCUTOFF   1 // when does nightbrightness begin? 10pm
#define FLASHDELAY 250  // delay for startup "flashWords" sequence
#define SHIFTDELAY 500   // controls color shifting speed

#define MFIVE    0xF00000000000        
#define MTEN     0x5800000000000000
#define AQUARTER 0x80FE000000000000
#define TWENTY   0x7E00000000000000
#define HALF     0xF0000000000
#define PAST     0x7800000000
#define TO       0xC00000000
#define ONE      0x43
#define TWO      0xC040
#define THREE    0x1F0000
#define FOUR     0xF0
#define FIVE     0xF0000000
#define SIX      0xE00000
#define SEVEN    0x800F00
#define EIGHT    0x1F000000
#define NINE     0xF
#define TEN      0x1010100
#define ELEVEN   0x3F00
#define TWELVE   0xF600

#define NEOPIN D4 


class DisplayManager
{
public: 
    DisplayManager();
    void update();

private:
    Adafruit_NeoMatrix* matrix;
    uint64_t mask;
    int j = 0;

    void adjustBrightness();
    void displayTime();

    void applyMask();
    uint32_t Wheel(byte WheelPos);
    void rainbowCycle(uint8_t wait);

    void printDigits(int digits);

};

#endif /* DISPLAYMANAGER_H */
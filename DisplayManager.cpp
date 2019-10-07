#include "DisplayManager.h"

DisplayManager::DisplayManager(){
    
    matrix = new Adafruit_NeoMatrix(8, 8, NEOPIN,
                            NEO_MATRIX_TOP  + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB         + NEO_KHZ800);

    pinMode(NEOPIN, OUTPUT);

    matrix->begin();
    matrix->setBrightness(100);
    matrix->fillScreen(0);
    matrix->show();

}

void DisplayManager::update(){
    adjustBrightness();
    displayTime();

    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    
    Serial.println();
}

void DisplayManager::printDigits(int digits) {
 // utility function for digital clock display: prints preceding colon and leading 0
 Serial.print(":");
 if (digits < 10)
 Serial.print('0');
 Serial.print(digits);
}

void DisplayManager::adjustBrightness(){
  if (hour() < MORNINGCUTOFF || hour() > NIGHTCUTOFF) {
    matrix->setBrightness(NIGHTBRIGHTNESS);
  } else {
    matrix->setBrightness(DAYBRIGHTNESS);
  }
}

void DisplayManager::displayTime(){

  time_t theTime = now();

  uint64_t old_mask = mask;
  mask = 0;

  int currentMinute = minute();
  int currentHour = hour();

  if ((currentMinute > 4) && (currentMinute < 10)) {
    mask |= MFIVE;
    //Serial.print("five");
  }
  if ((currentMinute > 9) && (currentMinute < 15)) {
    mask |= MTEN;
    //Serial.print("ten");
  }
  if ((currentMinute > 14) && (currentMinute < 20)) {
    mask |= AQUARTER;
    //Serial.print("a quarter");
  }
  if ((currentMinute > 19) && (currentMinute < 25)) {
    mask |= TWENTY;
    //Serial.print("twenty");
  }
  if ((currentMinute > 24) && (currentMinute < 30)) {
    mask |= TWENTY;
    mask |= MFIVE;
    //Serial.print("twenty five");
  }
  if ((currentMinute > 29) && (currentMinute < 35)) {
    mask |= HALF;
    //Serial.print("half");
  }
  if ((currentMinute > 34) && (currentMinute < 40)) {
    mask |= TWENTY;
    mask |= MFIVE;
    //Serial.print("twenty five");
  }
  if ((currentMinute > 39) && (currentMinute < 45)) {
    mask |= TWENTY;
    //Serial.print("twenty");
  }
  if ((currentMinute > 44) && (currentMinute < 50)) {
    mask |= AQUARTER;
    //Serial.print("a quarter");
  }
  if ((currentMinute > 49) && (currentMinute < 55)) {
    mask |= MTEN;
    //Serial.print("ten");
  }
  if (currentMinute > 54) {
    mask |= MFIVE;
    //Serial.print("five");
  }

  if ((currentMinute < 5))
  {
    switch (currentHour) {
      case 1:
      case 13:
        ONE;
        break;
      case 2:
      case 14:
        TWO;
        break;
      case 3:
      case 15:
        THREE;
        break;
      case 4:
      case 16:
        FOUR;
        break;
      case 5:
      case 17:
        FIVE;
        break;
      case 6:
      case 18:
        SIX;
        break;
      case 7:
      case 19:
        SEVEN;
        break;
      case 8:
      case 20:
        EIGHT;
        break;
      case 9:
      case 21:
        NINE;
        break;
      case 10:
      case 22:
        TEN;
        break;
      case 11:
      case 23:
        ELEVEN;
        break;
      case 0:
      case 12:
        TWELVE;
        break;
    }

  }
  else if ((currentMinute < 35) && (currentMinute > 4))
  {
    mask |= PAST;
    //Serial.print(" past ");
    switch (currentHour) {
      case 1:
      case 13:
        mask |= ONE;
        break;
      case 2:
      case 14:
        mask |= TWO;
        break;
      case 3:
      case 15:
        mask |= THREE;
        break;
      case 4:
      case 16:
        mask |= FOUR;
        break;
      case 5:
      case 17:
        mask |= FIVE;
        break;
      case 6:
      case 18:
        mask |= SIX;
        break;
      case 7:
      case 19:
        mask |= SEVEN;
        break;
      case 8:
      case 20:
        mask |= EIGHT;
        break;
      case 9:
      case 21:
        mask |= NINE;
        break;
      case 10:
      case 22:
        mask |= TEN;
        break;
      case 11:
      case 23:
        mask |= ELEVEN;
        break;
      case 0:
      case 12:
        mask |= TWELVE;
        break;
    }
  }
  else
  {
    // if we are greater than 34 minutes past the hour then display
    // the next hour, as we will be displaying a 'to' sign
    mask |= TO;
    //Serial.print(" to ");
    switch (currentHour) {
      case 1:
      case 13:
       mask |=  TWO;
        break;
      case 14:
      case 2:
        mask |= THREE;
        break;
      case 15:
      case 3:
        mask |= mask |= FOUR;
        break;
      case 4:
      case 16:
        mask |= FIVE;
        break;
      case 5:
      case 17:
        mask |= SIX;
        break;
      case 6:
      case 18:
        mask |= SEVEN;
        break;
      case 7:
      case 19:
        mask |= EIGHT;
        break;
      case 8:
      case 20:
        mask |= NINE;
        break;
      case 9:
      case 21:
        mask |= TEN;
        break;
      case 10:
      case 22:
        mask |= ELEVEN;
        break;
      case 11:
      case 23:
        mask |=  TWELVE;
        break;
      case 0:
      case 12:
        mask |= ONE;
        break;
    }
  }
    applyMask(); // apply phrase mask to colorshift function
}

void DisplayManager::applyMask() {

  for (byte i = 0; i < 64; i++) {
    boolean masker = bitRead(mask, 63 - i); // bitread is backwards because bitRead reads rightmost digits first. could have defined the word masks differently
    switch (masker) {
      case 0:
        matrix->setPixelColor(i, 0, 0, 0);
        break;
      case 1:
        matrix->setPixelColor(i, Wheel(((i * 256 / matrix->numPixels()) + j) & 255));
        //matrix->setPixelColor(i, WHITE);
        break;
    }
  }

  matrix->show(); // show it!
  delay(SHIFTDELAY);
  j++; // move the colors forward
  j = j % (256 * 5);

  // reset mask for next time
  mask = 0;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t DisplayManager::Wheel(byte WheelPos) {

  WheelPos = 255 - WheelPos;
  uint32_t wheelColor;

  if (WheelPos < 85) {
    wheelColor = matrix->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    wheelColor = matrix->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    wheelColor = matrix->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }

  // convert from 24-bit to 16-bit color - NeoMatrix requires 16-bit. perhaps there's a better way to do this.
  uint32_t bits = wheelColor;
  uint32_t blue = bits & 0x001F;     // 5 bits blue
  uint32_t green = bits & 0x07E0;    // 6 bits green
  uint32_t red = bits & 0xF800;      // 5 bits red

  // Return shifted bits with alpha set to 0xFF
  return (red << 8) | (green << 5) | (blue << 3) | 0xFF000000;
}


// Slightly different, this makes the rainbow equally distributed throughout
void DisplayManager::rainbowCycle(uint8_t wait) {
  
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < matrix->numPixels(); i++) {
      matrix->setPixelColor(i, Wheel(((i * 256 / matrix->numPixels()) + j) & 255));
    }
    matrix->show();
    delay(wait);
  }
}
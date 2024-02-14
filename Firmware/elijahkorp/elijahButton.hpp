#pragma onces

#include <Arduino.h>
#include <Surenoo.h>
#include <Wire.h>

#define POSITIVE_BUTTON PB3      // latch 1
#define POSITIVE_BUTTON_LED PB4  // led

#define NEGATIVE_BUTTON PB8      // latch 2
#define NEGATIVE_BUTTON_LED PB9  // led

#define SET_BUTTON PB10      // latch 3
#define SET_BUTTON_LED PB11  // led

class Button
{
  public:
    static int hourCount;
    static int minuteCount;
    static int setButtonCount; 

    Button();
    void positive(char time_nature);
    void negative(char time_nature); 
    uint8_t set(); 
};
extern SURENOO Surenoo;
extern Button button; 
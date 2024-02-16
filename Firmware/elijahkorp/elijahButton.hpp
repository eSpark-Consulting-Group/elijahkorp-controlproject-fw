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

#define LIGHT_BUTTON PB12      // latch 3
#define LIGHT_BUTTON_LED PB13  // led

#define PUMP_BUTTON PB14      // latch 3
#define PUMP_BUTTON_LED PB15  // led

#define RELAY_1 PA0     // latch 3
#define RELAY_2 PA1      // latch 3

// namespace set
// {
//   typedef enum
//   {
//     realTimeHour=0,
//     realTimeMinute,
//     realTimePeriod,
//     ledOnTimeHour,
//     ledOnTimeMinute,
//     ledOnTimePeriod,
//     ledOffTimeHour,
//     ledOffTimeMinute,
//     ledOffTimePeriod,
//   }setButton;
// }
class Button
{
  public:
    static int hourCount;
    static int minuteCount;
    static int setButtonCount; 

    Button();
    void positive(char time_nature);
    void negative(char time_nature); 
    bool isSetButtonPressed();
    int set(); 
};
extern SURENOO Surenoo;
extern Button button; 
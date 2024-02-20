#pragma onces

#include"LCD.hpp"


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


typedef enum
  {
    CURRENT_TIME_HOUR = 0,
    CURRENT_TIME_MINUTE,
    CURRENT_TIME_PERIOD,
    ON_TIME_HOUR,
    ON_TIME_MINUTE,
    ON_TIME_PERIOD,
    OFF_TIME_HOUR,
    OFF_TIME_MINUTE,
    OFF_TIME_PERIOD,
}set;

class Button
{
  public:
    static int hourCount;
    static int minuteCount;
    static int setButtonCount; 

    Button();
    void positive(const char* time_nature);
    void negative(const char* time_nature);
    void lightOverRide();
    void pumpOverRide();
    bool isHourCountLessThanNine(); 
    bool isHourCountGreaterThanNine();
    bool isMinuteCountLessThanNine();
    bool isMinuteCountGreaterThanNine();
    bool isSetButtonPressed();
    int set(); 
};

extern Button button; 
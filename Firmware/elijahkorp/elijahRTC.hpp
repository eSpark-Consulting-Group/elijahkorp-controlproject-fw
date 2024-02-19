#pragma onces

#include <STM32RTC.h>


class realTimeClock
{
  public:
    char amPmDayNight[3];
    char realtime[50];
    char lightOntime[50];
    char lightOfftime[50];
    byte realTimeMinutes = 0;
    byte realTimehours = 0;
    
    byte realSeconds = 0;
    byte seconds = 0;
    byte minutes = 0;
    byte hours = 0;
    static STM32RTC::AM_PM  realTimeperiod ;
    static STM32RTC::Hour_Format hourFormat;
    static STM32RTC::AM_PM period;

    void setUp();
    void nightPeriod(char* timing);
    void morningPeriod(char* timing);
    const char* periodToString(STM32RTC::AM_PM period);
    void loop();
    void updateTime();
    void setLightOn();
    void setLightOff();
    void turnOnLedRelay_2(char* realtime);
    void turnOffLedRelay_2(char* realtime);
    void pumpRelayOnandOffInterval(uint8_t sec);
    void setHoursOrMinute(char time_nature);
    void dayNightIndicator();
};
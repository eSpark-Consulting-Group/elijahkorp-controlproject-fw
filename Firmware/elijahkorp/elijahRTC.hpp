#pragma onces

#include <STM32RTC.h>


class realTimeClock
{
  public:
    char amPmDayNight[3];
    char realtime[50];
    char lightOntime[50];
    char lightOfftime[50];
    byte seconds = 0;
    byte minutes = 43;
    byte hours = 3;
    static STM32RTC::Hour_Format hourFormat;
    static STM32RTC::AM_PM period;

    void setUp();
    void nightPeriod(char* timing);
    void morningPeriod(char* timing);
    const char* periodToString(STM32RTC::AM_PM period);
    void loop();
    void updateTime();
    void setLightOn();
    void setHoursOrMinute(char time_nature);
    void dayNightIndicator();
};
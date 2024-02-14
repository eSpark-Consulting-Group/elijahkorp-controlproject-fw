#pragma onces

class realTimeClock
{
  public:
    char amPmDayNight[3]; 
    void setHoursOrMinute(char time_nature);
    void dayNightIndicator();
};
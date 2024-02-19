#include"elijahRTC.hpp"
#include"elijahButton.hpp"

STM32RTC::Hour_Format realTimeClock::hourFormat = STM32RTC::HOUR_24;
STM32RTC::AM_PM realTimeClock::period = STM32RTC::PM;
STM32RTC::AM_PM realTimeClock::realTimeperiod = STM32RTC::PM;
STM32RTC& rtclock = STM32RTC::getInstance();


void realTimeClock::setUp()
{
  Serial.println("RTC Init");
  rtclock.begin(hourFormat);
  rtclock.setHours(realTimehours, period);
  rtclock.setMinutes(realTimeMinutes);
  rtclock.setSeconds(realSeconds);
}

void realTimeClock::loop()
{
    uint8_t sec = 0;
    uint8_t mn = 0;
    uint8_t hrs = 0;
    uint32_t subs = 0;
    
    rtclock.getTime(&hrs, &mn, &sec, &subs);
    snprintf(realtime, sizeof(realtime), "%02d:%02d:%02d:%2s", hrs, mn, sec,periodToString(period));
    morningPeriod(realtime);
    nightPeriod(realtime);  
    // Serial.println(realtime);
    Surenoo.setCursorlcd(0, 0);
    Surenoo.print("Redible Wall");
    Surenoo.setCursorlcd(0, 1);
    Surenoo.print(realtime);

    // rtclock.getTime(&hrs, &mn, &sec, &subs);
    // snprintf(realtime, sizeof(realtime), "%02d:%02d:%02d:%2s", hrs, mn, sec, periodToString(period));

    // Check if it's time to toggle the pump relay
     unsigned long currentTime = millis() / 1000; // Convert milliseconds to seconds
     Serial.println(currentTime);

    
     turnOnLedRelay_2(realtime);
     turnOffLedRelay_2(realtime);
     pumpRelayOnandOffInterval(sec);
     button.lightOverRide();
     button.pumpOverRide();
}

void realTimeClock::updateTime()
{
    realTimeMinutes = button.minuteCount;
    realTimehours = button.hourCount;
    if (strcmp(amPmDayNight, "AM") == 0)
      realTimeperiod = STM32RTC::AM;
    if (strcmp(amPmDayNight, "PM") == 0)
      realTimeperiod = STM32RTC::PM;
}

void realTimeClock::setLightOn()
{
    minutes = button.minuteCount;
    hours = button.hourCount;
    if (strcmp(amPmDayNight, "AM") == 0)
      period = STM32RTC::AM;
    if (strcmp(amPmDayNight, "PM") == 0)
      period = STM32RTC::PM;
    snprintf(lightOntime, sizeof(lightOntime), "%02d:%02d:%02d:%2s", hours, minutes, seconds,periodToString(period));
    Serial.println(lightOntime);
}

void realTimeClock::setLightOff()
{
    minutes = button.minuteCount;
    hours = button.hourCount;
    if (strcmp(amPmDayNight, "AM") == 0)
      period = STM32RTC::AM;
    if (strcmp(amPmDayNight, "PM") == 0)
      period = STM32RTC::PM;
    snprintf(lightOfftime, sizeof(lightOntime), "%02d:%02d:%02d:%2s", hours, minutes, seconds,periodToString(period));
    Serial.println(lightOfftime);
}


void realTimeClock::nightPeriod(char* realtime)
{
  if(strcmp(realtime, "13:00:00:PM") == 0)
    {
       seconds = 0;
       minutes = 0;
       hours = 0;
       period = STM32RTC::AM;
       setUp();
    }
}

void realTimeClock::morningPeriod(char* realtime)
{
  if (strcmp(realtime, "13:00:00:AM") == 0)
    {
       seconds = 0;
       minutes = 0;
       hours = 0;
       period = STM32RTC::PM;
       setUp();
    }
}

void realTimeClock::turnOnLedRelay_2(char* realtime)
{
  if(strcmp(realtime, lightOntime) == 0)
    {
       digitalWrite(LIGHT_BUTTON_LED, LOW);
       digitalWrite(RELAY_2, HIGH);
       Serial.println("LED REALY_2 ON:::");
    }
}

void realTimeClock::turnOffLedRelay_2(char* realtime)
{
  if(strcmp(realtime, lightOfftime) == 0)
    {
       digitalWrite(LIGHT_BUTTON_LED, HIGH);
       digitalWrite(RELAY_2, LOW);
       Serial.println("LED REALY_2 OFF:::");
    }
}

void realTimeClock::pumpRelayOnandOffInterval(uint8_t sec) //// NOTE THIS SHOULD BE DONE BY USING RTC ******************WRONG*********************************
{

    if ((sec % 10) < 2) 
    {
        Serial.println("Relay_ 1 ON for 2.5");
        digitalWrite(RELAY_1, HIGH );
    }
    else 
    {
        Serial.println("Relay_1 OFF for 7.5sec");
        digitalWrite(RELAY_1, LOW );
    }
}

const char* realTimeClock::periodToString(STM32RTC::AM_PM period) 
{
    switch (period) 
    {
        case STM32RTC::AM: 
          return "AM";
        case STM32RTC::PM: 
          return "PM";
        default: 
          return "UNKNOWN";
    }
}

void realTimeClock::setHoursOrMinute(char time_nature) 
{
  int limit = 0;
  int row = 1, col = 0;
  if (time_nature == 'H') 
  {
    col = 1;
    limit = 12;
  } 
  else if (time_nature == 'M') 
  {
    col = 4;
    limit = 59;
  } 
  else 
  {
    Surenoo.clearlcd();
    Surenoo.setCursorlcd(0, 0);
    Surenoo.print("Error");
    return;
  }

  button.positive(time_nature);
  button.negative(time_nature);
 
  Serial.println(time_nature);
  if ((button.hourCount <= 9 && button.hourCount >= 0) && time_nature == 'H') 
  {
    Surenoo.setCursorlcd(col, 1);
    Surenoo.print(button.hourCount);
  } 
  else if (button.hourCount > 9 && time_nature == 'H') 
  {
    Surenoo.setCursorlcd(col - 1, 1);
    Surenoo.print(button.hourCount);
  }
  else if ((button.minuteCount <= 9 && button.minuteCount >= 0) && time_nature == 'M') 
  {
    Surenoo.setCursorlcd(col, 1);
    Surenoo.print(button.minuteCount);
  }  
  else if (button.minuteCount > 9 && time_nature == 'M') 
  {
    Surenoo.setCursorlcd(col - 1, 1);
    Surenoo.print(button.minuteCount);
  }  
  else 
  {
    Serial.println("Error from setHoursOrMinute");
  }
}

void realTimeClock::dayNightIndicator()
{
  if (digitalRead(POSITIVE_BUTTON) == LOW) 
  {
    strcpy(amPmDayNight, "AM");
    Surenoo.setCursorlcd(6, 1);
    Surenoo.print("AM");
    digitalWrite(POSITIVE_BUTTON_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(POSITIVE_BUTTON_LED, HIGH);  // Turn on LED
  }

  if (digitalRead(NEGATIVE_BUTTON) == LOW) 
  {
    strcpy(amPmDayNight, "PM");
    Surenoo.setCursorlcd(6, 1);
    Surenoo.print("PM");
    digitalWrite(NEGATIVE_BUTTON_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(NEGATIVE_BUTTON_LED, HIGH);  // Turn on LED
  }

}



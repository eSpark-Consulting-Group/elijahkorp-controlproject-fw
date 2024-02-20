#include"elijahRTC.hpp"
#include"elijahButton.hpp"

STM32RTC::Hour_Format realTimeClock::hourFormat = STM32RTC::HOUR_24;
STM32RTC::AM_PM realTimeClock::period = STM32RTC::PM;
STM32RTC::AM_PM realTimeClock::CURRENT_TIME_PERIOD = STM32RTC::PM;
STM32RTC& rtclock = STM32RTC::getInstance();


void realTimeClock::setUp()
{
  Serial.println("RTC Init");
  rtclock.begin(hourFormat);
  rtclock.setHours(CURRENT_TIME_HOURs, period);
  rtclock.setMinutes(CURRENT_TIME_MINUTEs);
  rtclock.setSeconds(realSeconds);
}

void realTimeClock::loop()
{
    uint8_t sec = 0;
    uint8_t mn = 0;
    uint8_t hrs = 0;
    uint32_t subs = 0;
    
    rtclock.getTime(&hrs, &mn, &sec, &subs);
    snprintf(realtime, sizeof(realtime), "%02d:%02d:%02d:%2s", hrs, mn, sec,periodToString(period)); //current time is stored in the real time variable
    morningPeriod(realtime);   // Find  "AM" from the real time 
    nightPeriod(realtime);      // Find  "PM" from the real time 
    Surenoo.setCursorlcd(0, 0);
    Surenoo.print("Redible Wall");
    Surenoo.setCursorlcd(0, 1);
    Surenoo.print(realtime);  //print Current time on the LCD
    turnOnLedRelay_2(realtime); //LED's Relay will ON when it matches the Realtime/Current time
    turnOffLedRelay_2(realtime); //LED's Relay will OFF when it matches the Realtime/Current time
    pumpRelayOnandOffInterval(sec);  //Pump Relay will ON for 2.5sec and OFF for 7.5 sec
    button.lightOverRide();   //LED will ON on Pressing and OFF on the releasing 
    button.pumpOverRide();    //Pump LED will ON on Pressing and OFF on the releasing 
}

void realTimeClock::updateTime()
{
    CURRENT_TIME_MINUTEs = button.minuteCount;
    CURRENT_TIME_HOURs = button.hourCount;
    if (strcmp(amPmDayNight, "AM") == 0)
      CURRENT_TIME_PERIOD = STM32RTC::AM;
    if (strcmp(amPmDayNight, "PM") == 0)
      CURRENT_TIME_PERIOD = STM32RTC::PM;
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

void realTimeClock::pumpRelayOnandOffInterval(uint8_t sec) 
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

void realTimeClock:: setHoursOrMinute(const char* time_nature, int count) 
{
  if (!strcmp(time_nature, "Hours")) 
  {
    col = 1;
    limit = 12;
  } 
  else if (time_nature == "Minute") 
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
  
  if (button.isHourCountLessThanNine() && time_nature == "Hours") 
  {
    sprintf(buf, "%d", button.hourCount);
    surenooLed.blinkText(buf, col, row);
    // 'count' refers to the next value selected by pressing the hold button.
    // When the set button is pressed, the blinking of the previous hourCount stops,
    // and the program counter starts blinking the minuteCount.
    surenooLed.printHold(count, buf, col);                 
  } 
  else if (button.isHourCountGreaterThanNine() && time_nature == "Hours") 
  {
    sprintf(buf, "%d", button.hourCount);
    surenooLed.blinkText(buf, col - 1, row);
    // 'count' refers to the next value selected by pressing the hold button.
    // When the set button is pressed, the blinking of the previous hourCount stops,
    // and the program counter starts blinking the minuteCount.
    surenooLed.printHold(count, buf, col - 1);
  }
  else if (button.isMinuteCountLessThanNine() && time_nature == "Minute") 
  {
    sprintf(buf, "%d", button.minuteCount);
    surenooLed.blinkText(buf, col, row);
    // 'count' refers to the next value selected by pressing the hold button.
    // When the set button is pressed, the blinking of the previous minuteCount stops,
    // and the program counter starts blinking the AM/PM period.
    surenooLed.printHold(count, buf, col);
  }  
  else if (button.isMinuteCountGreaterThanNine() && time_nature == "Minute") 
  {
    sprintf(buf, "%d", button.minuteCount);
    surenooLed.blinkText(buf, col - 1, row);
    // 'count' refers to the next value selected by pressing the hold button.
    // When the set button is pressed, the blinking of the previous minuteCount stops,
    // and the program counter starts blinking the AM/PM period.
    surenooLed.printHold(count, buf, col - 1);
  }  
  else 
  {
    Serial.println("Error from setHoursOrMinute");
  }
}

void realTimeClock::dayNightIndicator(int count)
{
  if (digitalRead(POSITIVE_BUTTON) == LOW) 
  {
    strcpy(amPmDayNight, "AM");
    
    if(button.set() == count) 
    {
       Surenoo.setCursorlcd(6, 1);
       Surenoo.print("AM");
    }
    digitalWrite(POSITIVE_BUTTON_LED, LOW);  // Turn oN LED
  } 
  else 
  {
    digitalWrite(POSITIVE_BUTTON_LED, HIGH);  // Turn oFF LED
  }

  if (digitalRead(NEGATIVE_BUTTON) == LOW) 
  {
    strcpy(amPmDayNight, "PM");
    if(button.set() == count)
    {
       Surenoo.setCursorlcd(6, 1);
       Surenoo.print("PM");
    }
    digitalWrite(NEGATIVE_BUTTON_LED, LOW);   // Turn oN LED
  } 
  else 
  {
    digitalWrite(NEGATIVE_BUTTON_LED, HIGH);  // Turn oFF LED
  }
  surenooLed.blinkText(amPmDayNight, 6, 1);  //col =6 , row  = 1

}



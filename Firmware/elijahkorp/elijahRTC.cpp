#include"elijahRTC.hpp"
#include"elijahButton.hpp"


// char realTimeClock::amPmDayNight[3];

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
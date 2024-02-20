#include"elijahButton.hpp"


int Button::hourCount = 0;
int Button::minuteCount = 0;
int Button::setButtonCount = 0;

SURENOO Surenoo;
Button button;

Button::Button()
{
  pinMode(POSITIVE_BUTTON, INPUT);
  pinMode(POSITIVE_BUTTON_LED, OUTPUT);
  
  pinMode(NEGATIVE_BUTTON, INPUT);
  pinMode(NEGATIVE_BUTTON_LED, OUTPUT);

  pinMode(SET_BUTTON, INPUT);
  pinMode(SET_BUTTON_LED, OUTPUT);

  pinMode(LIGHT_BUTTON, INPUT);
  pinMode(LIGHT_BUTTON_LED, OUTPUT);

  pinMode(PUMP_BUTTON, INPUT);
  pinMode(PUMP_BUTTON_LED, OUTPUT);

  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);

  digitalWrite(LIGHT_BUTTON_LED, HIGH);
  digitalWrite(PUMP_BUTTON_LED, HIGH);
}

void Button::positive(const char* time_nature) 
{
  if (digitalRead(POSITIVE_BUTTON) == LOW) 
  {
    // Increment the count only if the button was not pressed previously (latching action)
    if (digitalRead(POSITIVE_BUTTON_LED) == HIGH) 
    {
      if (time_nature == "Hours")
      {
        hourCount++;
        Serial.println("Hour incremented");
        digitalWrite(SET_BUTTON_LED, LOW);  // Turn on Set button LED
        if (hourCount> 12)
          {
            hourCount = 0;
            Surenoo.setCursorlcd(0, 1);
            Surenoo.print(0);
          }
        
      }
      else if (time_nature == "Minute")
      {
        minuteCount++;
        if (minuteCount > 60)
            {
              minuteCount = 0;
              Surenoo.setCursorlcd(3, 1);
              Surenoo.print(0);
            }
        
        Serial.println("Minute incremented");
      }
      else
      {
        Serial.println("Error from positiveButton");
        return;
      }
    }
    digitalWrite(POSITIVE_BUTTON_LED, LOW);  // Turn On LED
  } 
  else 
  {
    digitalWrite(POSITIVE_BUTTON_LED, HIGH);  // Turn OFF Button+ LED
  }
}

void Button::negative(const char* time_nature) 
{
  if (digitalRead(NEGATIVE_BUTTON) == LOW) 
  {
    // decrement the count only if the button was not pressed previously (latching action)
    if (digitalRead(NEGATIVE_BUTTON_LED) == HIGH) 
    {
      if (time_nature == "Hours")
      {
        hourCount--;
        if (hourCount< 0)
            hourCount = 12;
        if(hourCount <= 9)
            {
              Surenoo.setCursorlcd(0, 1);
              Surenoo.print("0");
            }    
        Serial.println("Hour decremented");
      }
      else if (time_nature == "Minute")
      {
        minuteCount--;
        if (minuteCount <0)
              minuteCount = 59;

        if(hourCount <= 9)
            {
              Surenoo.setCursorlcd(3, 1);
              Surenoo.print("0");
            }   
        Serial.println("Minute decremented");
      }
      else
      {
        Serial.println("Error from negativeButton");
        return;
      }
    }
    digitalWrite(NEGATIVE_BUTTON_LED, LOW);  // Turn oN LED
  } 
  else 
  {
    digitalWrite(NEGATIVE_BUTTON_LED, HIGH);  // Turn oFF Button- LED
  }
}

void Button::lightOverRide()
{
  if (digitalRead(LIGHT_BUTTON) == LOW) 
  {
    digitalWrite(LIGHT_BUTTON_LED, LOW);  // Turn oNN Button- LED
  }
  else 
  {
    digitalWrite(LIGHT_BUTTON_LED, HIGH);  // Turn oFF Button- LED
  }
}

void Button::pumpOverRide()
{
  if (digitalRead(PUMP_BUTTON) == LOW) 
  {
    digitalWrite(PUMP_BUTTON_LED, LOW);  // Turn oN Button- LED
  }
  else 
  {
    digitalWrite(PUMP_BUTTON_LED, HIGH);  // Turn oFF Button- LED
  }
}

bool Button::isHourCountLessThanNine()
{
  return button.hourCount <= 9 && button.hourCount >= 0;
}

bool Button::isHourCountGreaterThanNine()
{
  return button.hourCount > 9;
}

bool Button::isMinuteCountLessThanNine()
{
  return button.minuteCount <= 9 && button.minuteCount >= 0;
}

bool Button::isMinuteCountGreaterThanNine()
{
  return button.minuteCount > 9;
}

bool Button::isSetButtonPressed() 
{
  static bool wasPressed = false;
  bool isPressed = (digitalRead(SET_BUTTON) == LOW);

  if (isPressed && !wasPressed) 
  {
    // Button was just pressed
    digitalWrite(SET_BUTTON_LED, HIGH); // Turn on LED
  }
  else if (!isPressed && wasPressed) 
  {
    // Button was just released
    digitalWrite(SET_BUTTON_LED, LOW); // Turn off LED
  }

  wasPressed = isPressed; // Remember the button state for the next iteration
  return isPressed;
}

int Button::set() 
{
  // Check if the button is pressed
  
  if (digitalRead(SET_BUTTON) == LOW) 
  {
    // Increment the count only if the button was not pressed previously (latching action)
    if (digitalRead(SET_BUTTON_LED) == HIGH && !(digitalRead(POSITIVE_BUTTON) == LOW || digitalRead(NEGATIVE_BUTTON) == LOW)) 
    {
      setButtonCount ++;
    }
    digitalWrite(SET_BUTTON_LED, LOW);  // Turn oN LED
  } 
  else 
  {
    digitalWrite(SET_BUTTON_LED, HIGH);  // Turn oFF Set button LED
  }
  // for (int i=0 ;i <=setButtonCount ; i++)
  // {
  //   if (setButtonCount == i)
  //   {
  //     return button = (setButton)i;
  //   }
  // }
  return setButtonCount;
}
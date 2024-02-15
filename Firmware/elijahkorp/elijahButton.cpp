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
}
void Button::positive(char time_nature) 
{
  if (digitalRead(POSITIVE_BUTTON) == LOW) 
  {
    // Increment the count only if the button was not pressed previously (latching action)
    if (digitalRead(POSITIVE_BUTTON_LED) == HIGH) 
    {
      if (time_nature == 'H')
      {
        hourCount++;
        if (hourCount> 12)
          {
            hourCount = 0;
            Surenoo.setCursorlcd(0, 1);
            Surenoo.print(0);
          } 
        Serial.println("Hour incremented");
      }
      else if (time_nature == 'M')
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
    digitalWrite(POSITIVE_BUTTON_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(POSITIVE_BUTTON_LED, HIGH);  // Turn on LED
  }
}

void Button::negative(char time_nature) 
{
  if (digitalRead(NEGATIVE_BUTTON) == LOW) 
  {
    // decrement the count only if the button was not pressed previously (latching action)
    if (digitalRead(NEGATIVE_BUTTON_LED) == HIGH) 
    {
      if (time_nature == 'H')
      {
        hourCount--;
        if (hourCount< 0)
            hourCount = 0;
        if(hourCount <= 9)
            {
              Surenoo.setCursorlcd(0, 1);
              Surenoo.print("0");
            }    
        Serial.println("Hour incremented");
      }
      else if (time_nature == 'M')
      {
        minuteCount--;
        if (minuteCount <0)
              minuteCount = 0;

        if(hourCount <= 9)
            {
              Surenoo.setCursorlcd(3, 1);
              Surenoo.print("0");
            }   
        Serial.println("Minute incremented");
      }
      else
      {
        Serial.println("Error from negativeButton");
        return;
      }
    }
    digitalWrite(NEGATIVE_BUTTON_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(NEGATIVE_BUTTON_LED, HIGH);  // Turn on LED
  }
}

int Button::set() 
{
  //   // Check if the button is pressed
  
  if (digitalRead(SET_BUTTON) == LOW) 
  {
    // Increment the count only if the button was not pressed previously (latching action)
    if (digitalRead(SET_BUTTON_LED) == HIGH) 
    {
      setButtonCount ++;
    }
    digitalWrite(SET_BUTTON_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(SET_BUTTON_LED, HIGH);  // Turn on LED
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
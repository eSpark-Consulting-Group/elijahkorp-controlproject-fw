
#include <Surenoo.h>
#include <Wire.h>

#define Latch1 PB3      // latch 1
#define Latch1_LED PB4  // led

#define Latch2 PB8      // latch 2
#define Latch2_LED PB9  // led

#define Latch3 PB10      // latch 3
#define Latch3_LED PB11  // led

SURENOO Surenoo;

void setHoursOrMinute(char time_nature);
void positiveButton(char time_nature);
void negativeButton(char time_nature);
void dayNightIndicator();
uint8_t setButton();

static int hourCount = 0;
static int minuteCount = 0;
static int setButtonCount = 0; 
static char amPmDayNight[3];  

void setup() 
{
  Serial.begin(9600);

  pinMode(Latch1, INPUT);
  pinMode(Latch1_LED, OUTPUT);
  
  pinMode(Latch2, INPUT);
  pinMode(Latch2_LED, OUTPUT);

  pinMode(Latch3, INPUT);
  pinMode(Latch3_LED, OUTPUT);

  Surenoo.init();
  Surenoo.clearlcd();

  Surenoo.setCursorlcd(0, 0);
  Surenoo.print("Readible Wall");

  delay(5000);
  Surenoo.clearlcd();

  Surenoo.setCursorlcd(0, 0);
  Surenoo.print("SET TIME:");
  Surenoo.setCursorlcd(0, 1);
  Surenoo.print("0H:0M XX");
  Surenoo.noCursorlcd();
}

void loop() 
{

  // setHoursOrMinute('H');
  // Serial.println(count);

  switch(setButton())
  {
    case 0 :
       Serial.println("Hour");
       setHoursOrMinute('H');
       break;
    case 1 :
       Serial.println("Minute");
       setHoursOrMinute('M');
       break;
    case 2 :
       Serial.println("AM/PM Selection");
       dayTimeIndicator();  
       break;
    default:
        Serial.println("Done");
        break;    
  }
  //  setHoursOrMinute('M');
}

void setHoursOrMinute(char time_nature) 
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

  positiveButton(time_nature);
  negativeButton(time_nature);

  Serial.println(time_nature);
  if ((hourCount <= 9 && hourCount >= 0) && time_nature == 'H') 
  {
    Surenoo.setCursorlcd(col, 1);
    Surenoo.print(hourCount);
  } 
  else if (hourCount > 9 && time_nature == 'H') 
  {
    Surenoo.setCursorlcd(col - 1, 1);
    Surenoo.print(hourCount);
  }
  else if ((minuteCount <= 9 && minuteCount >= 0) && time_nature == 'M') 
  {
    Surenoo.setCursorlcd(col, 1);
    Surenoo.print(minuteCount);
  }  
  else if (minuteCount > 9 && time_nature == 'M') 
  {
    Surenoo.setCursorlcd(col - 1, 1);
    Surenoo.print(minuteCount);
  }  
  else 
  {
    Serial.println("Error from setHoursOrMinute");
  }
}

void positiveButton(char time_nature) 
{
  if (digitalRead(Latch1) == LOW) 
  {
    // Increment the count only if the button was not pressed previously (latching action)
    if (digitalRead(Latch1_LED) == HIGH) 
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
    digitalWrite(Latch1_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(Latch1_LED, HIGH);  // Turn on LED
  }
}

void negativeButton(char time_nature) 
{
  if (digitalRead(Latch2) == LOW) 
  {
    // decrement the count only if the button was not pressed previously (latching action)
    if (digitalRead(Latch2_LED) == HIGH) 
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
    digitalWrite(Latch2_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(Latch2_LED, HIGH);  // Turn on LED
  }
}

void dayTimeIndicator()
{
  if (digitalRead(Latch1) == LOW) 
  {
    strcpy(amPmDayNight, "AM");
    Surenoo.setCursorlcd(6, 1);
    Surenoo.print("AM");
    digitalWrite(Latch1_LED, LOW);  // Turn off LED
  } 
  else 
  {
    
    digitalWrite(Latch1_LED, HIGH);  // Turn on LED
  }

  if (digitalRead(Latch2) == LOW) 
  {
    strcpy(amPmDayNight, "PM");
    Surenoo.setCursorlcd(6, 1);
    Surenoo.print("PM");
    digitalWrite(Latch2_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(Latch2_LED, HIGH);  // Turn on LED
  }

}
uint8_t setButton() 
{
  //   // Check if the button is pressed
  
  if (digitalRead(Latch3) == LOW) 
  {
    // Increment the count only if the button was not pressed previously (latching action)
    if (digitalRead(Latch3_LED) == HIGH) 
    {
      setButtonCount ++;
    }
    digitalWrite(Latch3_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(Latch3_LED, HIGH);  // Turn on LED
  }
  return setButtonCount;
}
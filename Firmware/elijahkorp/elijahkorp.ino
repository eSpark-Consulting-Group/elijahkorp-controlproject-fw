// This library is for the Surenoo 16x2 RGB LCD display.
// The LCD contains a AIP31068 chip for the LCD and a
// PCA9633 chip for the RGB. But only 3 are connected.
// Both libraries are standard available but for more
// easy use they are combined. The C++/C I kept as much
// original but unnecessary routines I have left.
// Variables can be changed in the .h file.

#include <Surenoo.h>
#include <Wire.h>

#define Latch1 PB3      // latch 1
#define Latch1_LED PB4  // led

SURENOO Surenoo;

void setHoursOrMinute(char time_nature);
void increaseTimeDigit();
static int count = 0;

void setup() 
{
  pinMode(Latch1, INPUT);
  pinMode(Latch1_LED, OUTPUT);

  Surenoo.init();
  Surenoo.clearlcd();

  Surenoo.setCursorlcd(0, 0);
  Surenoo.print("Readible Wall");

  delay(5000);
  Surenoo.clearlcd();

  Surenoo.setCursorlcd(0, 0);
  Surenoo.print("SET TIME:");
  Surenoo.setCursorlcd(0, 1);
  Surenoo.print("HH:MM AM");
  Surenoo.noCursorlcd();
}

void loop() 
{

  setHoursOrMinute('H');
  Serial.println(count);
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


  increaseTimeDigit();
  if (count > 9) 
  {
    Surenoo.setCursorlcd(col - 1, 1);
    Surenoo.print(count);
  } 
  else 
  {
    Surenoo.setCursorlcd(col, 1);
    Surenoo.print(count);
  }
}

void increaseTimeDigit() 
{
  //   // Check if the button is pressed
  if (digitalRead(Latch1) == LOW) 
  {
    // Increment the count only if the button was not pressed previously (latching action)
    if (digitalRead(Latch1_LED) == HIGH) 
    {
      count++;
    }
    digitalWrite(Latch1_LED, LOW);  // Turn off LED
  } 
  else 
  {
    digitalWrite(Latch1_LED, HIGH);  // Turn on LED
  }
}
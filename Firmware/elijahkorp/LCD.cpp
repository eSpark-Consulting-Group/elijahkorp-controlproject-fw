#include"LCD.hpp"
#include"elijahButton.hpp"

SURENOOLED surenooLed;

void SURENOOLED::blinkText(char* message, int col, int row)
{
 unsigned long currentMillis = millis();
  Surenoo.setCursorlcd(col, row);
  if(currentMillis - previousMillis > Blink_interval)   {
    previousMillis = currentMillis;
    if(BlankOnOff){
      for(i = 1; i < strlen(message)+1; i++) {
        Surenoo.print(" ");
      } //End For
    } // End If
    else {
      Surenoo.print(message);
    } //End Else
    BlankOnOff = !BlankOnOff;
  } //End If
}

void SURENOOLED::printHold(uint8_t count, char* message, uint8_t col, uint8_t row)
{
  if(button.set() == count)
    {
      Surenoo.setCursorlcd(col, row);
      Surenoo.print(message);
    }
}

void SURENOOLED::printNextScreen(char* message, int count, int col_1,int row_1, int col_2,int row_2)
{
  if(button.set() == count)
    {
    button.hourCount = 0;
    button.minuteCount = 0;
    Surenoo.setCursorlcd(col_1, row_1);
    Surenoo.print(message);
    Surenoo.setCursorlcd(col_2, row_2);
    Surenoo.print("00:00:XX");
    } 
}

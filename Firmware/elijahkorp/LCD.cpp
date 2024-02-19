#include"LCD.hpp"

SURENOOLED surenooLed;

void SURENOOLED::blinkText(char* msgtxt, int col, int row)
{
 unsigned long currentMillis = millis();
  Surenoo.setCursorlcd(col, row);
  if(currentMillis - previousMillis > Blink_interval)   {
    previousMillis = currentMillis;
    if(BlankOnOff){
      for(i = 1; i < strlen(msgtxt)+1; i++) {
        Surenoo.print(" ");
      } //End For
    } // End If
    else {
      Surenoo.print(msgtxt);
    } //End Else
    BlankOnOff = !BlankOnOff;
  } //End If
}
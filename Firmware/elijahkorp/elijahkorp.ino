
#include <Surenoo.h>
#include <Wire.h>
#include"elijahButton.hpp"
#include"elijahRTC.hpp"
 
realTimeClock rtc;
 

void setup() 
{
  Serial.begin(9600);
  rtc.setUp();

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

  switch(button.set())
  {
    case 0 :
       {
        Serial.println("Hour");
        rtc.setHoursOrMinute('H');
        break;
       }
    case 1 :
      {
       Serial.println("Minute");
       rtc.setHoursOrMinute('M');
       break;
       }
    case 2 :
      {
       Serial.println("AM/PM Selection");
       rtc.dayNightIndicator();
       rtc.updateTime();  
       break;
      }
    default:
       { 
        rtc.loop(); 
        Serial.println("Done");
        break;
       }   
       
        
  }
}






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
       if(button.set() == 3)
       {
        button.hourCount = 0;
        button.minuteCount = 0;
        Surenoo.setCursorlcd(0, 0);
        Surenoo.print("Set On Time");
        Surenoo.setCursorlcd(0, 1);
        Surenoo.print("00:00:XX");
       } 
       break;
      }
    case 3 ://LEd On time
       {
        Serial.println("LEd ON time");
        rtc.setHoursOrMinute('H');
        
        break;
       }
    case 4 :
      {
       Serial.println("Minute");
       rtc.setHoursOrMinute('M');
       break;
       }
    case 5 :
      {
       Serial.println("AM/PM Selection");
       rtc.dayNightIndicator();
       rtc.setLightOn(); 
       if(button.set() == 6)
       {
        button.hourCount = 0;
        button.minuteCount = 0;
        Surenoo.setCursorlcd(0, 0);
        Surenoo.print("Set OFF Time");
        Surenoo.setCursorlcd(0, 1);
        Surenoo.print("00:00:XX");
       } 
       break;
      }
    case 6 ://LEd OFF time
       {
        Serial.println("LEd OFF time");
        rtc.setHoursOrMinute('H');
        // button.hourCount = 0;
        // button.minuteCount = 0;
        // Surenoo.setCursorlcd(0, 0);
        // Surenoo.print("Set OFF Time");
        // Surenoo.setCursorlcd(0, 1);
        // Surenoo.print("00:00:XX");
        break;
       }
    case 7 :
      {
       Serial.println("Minute");
       rtc.setHoursOrMinute('M');
       break;
       }
    case 8 :
      {
       Serial.println("AM/PM Selection");
       rtc.dayNightIndicator();
       rtc.setLightOff();  
       break;
      }     
    default:
       { 
        rtc.loop(); 
        // Serial.println("Done");
        Serial.println(rtc.lightOntime);
        Serial.println(rtc.lightOfftime);
        break;
       }   
       
        
  }
}





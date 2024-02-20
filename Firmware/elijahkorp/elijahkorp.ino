
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
  Surenoo.print("00:00 XX");
  Surenoo.noCursorlcd();
}

void loop() 
{
  set buttonCount = static_cast<set>(button.set());
  switch(buttonCount)
  {
    case  set::CURRENT_TIME_HOUR :
        Serial.println("Hour");
        rtc.setHoursOrMinute("Hours", buttonCount+1);  //next case count value for holding the hour display
        break;

    case set::CURRENT_TIME_MINUTE :
        Serial.println("Minute");
        rtc.setHoursOrMinute("Minute", buttonCount+1); //next case count value for holding the minute display
        break;

    case set::CURRENT_TIME_PERIOD :
       Serial.println("AM/PM Selection");
       rtc.dayNightIndicator(buttonCount+1);           //next case count value for holding the AM/PM display
       rtc.updateTime();                               // updating the current time variables  
       surenooLed.printNextScreen("Set On Time", static_cast<int>(set::ON_TIME_HOUR));
       break;

    case set::ON_TIME_HOUR :                           //LEd On time
        Serial.println("LED ON time");
        rtc.setHoursOrMinute("Hours", buttonCount+1);   //next case count value for holding the hour display
        break;

    case set::ON_TIME_MINUTE :
       Serial.println("Minute");
       rtc.setHoursOrMinute("Minute", buttonCount+1);   //next case count value for holding the minute display
       break;

    case set::ON_TIME_PERIOD :
       Serial.println("AM/PM Selection");
       rtc.dayNightIndicator(buttonCount+1);            //next case count value for holding the AM/PM display
       rtc.setLightOn();                                //To store the light "ON" time in the lightOntime variable 
       surenooLed.printNextScreen("Set OFF Time", static_cast<int>(set::OFF_TIME_HOUR));
       break;

    case set::OFF_TIME_HOUR :                           //LEd OFF time
        Serial.println("LED OFF time");
        rtc.setHoursOrMinute("Hours", buttonCount+1);   //next case count value for holding the hour display
        break;

    case set::OFF_TIME_MINUTE :
       Serial.println("Minute");
       rtc.setHoursOrMinute("Minute", buttonCount+1);   //next case count value for holding the minute display
       break;

    case set::OFF_TIME_PERIOD :
       Serial.println("AM/PM Selection"); 
       rtc.dayNightIndicator(buttonCount+1);           //next case count value for holding the AM/PM display
       rtc.setLightOff();                              //To store the light "OFF" time in the lightOntime variable 
       rtc.setUp();                                    //Clock time start now 
       break;
    
    default:
        rtc.loop();                                    //perform the function on the behalve of set On/OFF time and Pump relay On for 2.5  sec and Off for 7.5 sec
        Serial.println(rtc.lightOntime);
        Serial.println(rtc.lightOfftime);
        break;
        
  }
}





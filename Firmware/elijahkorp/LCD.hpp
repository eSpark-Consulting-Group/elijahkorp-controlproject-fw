#pragma once

#include <Arduino.h>
#include <Surenoo.h>
#include <Wire.h>

#define Blink_interval  500            // Set at top of source code file
extern SURENOO Surenoo;

class SURENOOLED
{
  private:
  unsigned long previousMillis = 0;
  bool BlankOnOff = false;
  int i = 0;

  public:
  void blinkText(char* msgtxt, int col, int row);
};
extern SURENOOLED surenooLed;

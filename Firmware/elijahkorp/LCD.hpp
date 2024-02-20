#pragma once

#include <Arduino.h>
#include <Surenoo.h>
#include <Wire.h>

#define Blink_interval  450  

class SURENOOLED
{
  private:
  unsigned long previousMillis = 0;
  bool BlankOnOff = false;
  int i = 0;

  public:
  void blinkText(char* message, int col, int row);
  void printHold(uint8_t count, char* message, uint8_t col, uint8_t row = 1);
  void printNextScreen(char* message, int count, int col_1 = 0, int row_1 = 0, int col_2 = 0, int row_2 = 1);
};
extern SURENOOLED surenooLed;
extern SURENOO Surenoo;
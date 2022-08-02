#include <Arduino.h>
#include <TM1637Display.h>
#include "RTClib.h"

#define CLK 2
#define DIO 3
RTC_DS1307 rtc;

const uint8_t SEG_KUCZ[] = {
  SEG_B | SEG_C | SEG_F | SEG_E | SEG_G,           // K
  SEG_F | SEG_B | SEG_C | SEG_D | SEG_E,           // U
  SEG_A | SEG_F | SEG_E | SEG_D,                   // C
  SEG_A | SEG_B | SEG_G | SEG_E | SEG_D            // Z
  };
  const uint8_t SEG_IS[] = {
   SEG_D ,                                               // nic
  SEG_F | SEG_E,                                  // I
  SEG_A | SEG_F | SEG_G | SEG_D | SEG_C,          // S
  SEG_D ,
                                                  // nic
  };


TM1637Display display(CLK, DIO);

void setup () {
  Serial.begin(57600);
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  display.setBrightness(0x0f);
  display.setSegments(SEG_KUCZ);
  delay(1000);
  display.setSegments(SEG_IS);
  delay(1000);
}

void loop()
{

  DateTime now = rtc.now();
  int hour = now.hour();
  int minute = now.minute();
    if (minute < 10){
      minute = 0 * pow(10, (int)log10(minute)+1) + minute; 
    }
  
display.showNumberDecEx(minute, 0, true, 2, 2);
display.showNumberDecEx(hour, 0x80>>3, true, 2, 0);

  delay(1000);

  display.showNumberDecEx(minute, 0, true, 2, 2);
display.showNumberDecEx(hour, 0b01000000, true, 2, 0);

  delay(1000);
}

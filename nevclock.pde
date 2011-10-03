#include <Time.h>

//    External Component Libs
#include "LCD_driver.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "WProgram.h"
#include "HardwareSerial.h"

#include "Button.h"

struct Point {
  int x;
  int y;
};
typedef struct Point Point;

// Application specific

enum {
  ModeTime,
  ModeSetTime,
  ModeSetAlarm,
  ModeLasers,
  
  ModeCount,
};
typedef int Mode;

char modeNames[][16] = {
  "nevclock",
  "Set Time",
  "Set Alarm",
  "Lasers!"
};

#define BUZZER_PIN 50

int lol = 0;
int amount = 1;
time_t alarmTime = 0;
BOOL alarmIsOn = 0;
BOOL alarmIsGoingOff = false;

Button b1, b2, b3;
Mode mode;

enum {
  AlarmEditOnOff,
  AlarmEditHour,
  AlarmEditMinute,
  AlarmEditSecond,
  
  AlarmEditCount,
};
typedef int AlarmEdit;
AlarmEdit alarmEdit = AlarmEditHour;


void setup()
{
  ioinit();           //Initialize I/O
  LCDInit();	    //Initialize the LCD
  LCDContrast(44);
  LCDClear(BLACK);    // Clear LCD to a solid color
  Button_init(&b1, kSwitch1_PIN);
  Button_init(&b2, kSwitch2_PIN);
  Button_init(&b3, kSwitch3_PIN);
  
  tmElements_t firstTime = {0, 0, 12, 2, 3, 10, 41};
  setTime(makeTime(firstTime));
  
  mode = ModeTime;
}

void drawClock(tmElements_t forWhen, char *b) {
  drawTextClock(forWhen, b);
  drawAnalogClock(forWhen, false);
}

void drawTextClock(tmElements_t forWhen, char *b) {
  char sep = forWhen.Second%2 ? ' ' : ':';
  sprintf(b, "%c %02d%c%02d%c%02d", alarmIsOn?'!':' ', forWhen.Hour, sep, forWhen.Minute, sep, forWhen.Second);
  LCDPutStr(b, 35, 20, WHITE, BLACK);
}

void drawAnalogClock(tmElements_t when, BOOL inverse) {
  int fColor = inverse ? BLACK : WHITE;
  int hColor = inverse ? BLACK : RED;
  int mColor = inverse ? BLACK : GREEN;
  int sColor = inverse ? BLACK : YELLOW;
  
   Point tl = {60, 35};
   int r = COL_HEIGHT*0.25;
   Point mid = {tl.x + r, tl.y + r};
   
   LCDDrawCircle(tl.x, tl.y, COL_HEIGHT*0.25, fColor, FULLCIRCLE);
   
   float hfrac = (when.Hour*SECS_PER_HOUR + when.Minute*SECS_PER_MIN + when.Second)/(float)(SECS_PER_DAY);
   Point hr = {
     mid.x - cos(hfrac*M_PI*4)*r,
     mid.y + sin(hfrac*M_PI*4)*r
   };
   LCDSetLine(mid.x, mid.y, hr.x, hr.y, hColor);
   
  float mfrac = (when.Minute*SECS_PER_MIN + when.Second)/(float)(SECS_PER_HOUR);
  Point mi = {
     mid.x - cos(mfrac*M_PI*2)*r*0.8,
     mid.y + sin(mfrac*M_PI*2)*r*0.8
   };
   LCDSetLine(mid.x, mid.y, mi.x, mi.y, mColor);
   
  Point se = {
     mid.x - cos((when.Second/30.)*M_PI)*r*0.9,
     mid.y + sin((when.Second/30.)*M_PI)*r*0.9
   };
   LCDSetLine(mid.x, mid.y, se.x, se.y, sColor);
}

static time_t oldTime = 0;

void loop()
{
  char b[64];
  
  if(Button_wasPressedNow(&b3) && !alarmIsGoingOff) {
    mode = (mode + 1) % ModeCount;
    alarmEdit = AlarmEditHour;
    LCDClear(BLACK);
  }
    
  // Erase last frame's graphics
  if(mode == ModeLasers) {
    LCDSetLine(60, 64, COL_HEIGHT, ROW_LENGTH-lol, BLACK);
    LCDSetLine(60, 64, COL_HEIGHT, lol, BLACK);
  }
  tmElements_t oldForWhen; breakTime(oldTime, oldForWhen);
  drawAnalogClock(oldForWhen, true);
  
  // Draw this frame's graphics
  LCDPutStr(modeNames[mode], 10, 35, WHITE, BLACK);
  
  time_t forWhen = mode == ModeSetAlarm ? alarmTime : now();
  tmElements_t forWhen2; breakTime(forWhen, forWhen2);
  oldTime = forWhen;
  
  drawClock(forWhen2, b);
  
  
  if(mode == ModeSetAlarm || mode == ModeSetTime) {
    if(Button_wasPressedNow(&b2)) {
      LCDClear(BLACK);
      alarmEdit = (alarmEdit + 1) % AlarmEditCount;
      if(mode == ModeSetTime && alarmEdit == AlarmEditOnOff) alarmEdit++;
    }
    if(Button_wasPressedNow(&b1)) {
      if(alarmEdit == AlarmEditOnOff) {
        alarmIsOn = !alarmIsOn;
      } else {
        time_t mul =( alarmEdit == AlarmEditHour) ? SECS_PER_HOUR : (alarmEdit == AlarmEditMinute) ? SECS_PER_MIN : 1;
        if(mode == ModeSetTime)
          adjustTime(mul);
        else if(mode == ModeSetAlarm)
          alarmTime += mul;
      }
    }
    
    LCDSetLine(54, 14 + 23*alarmEdit, 54, 14 + 23*alarmEdit + 17, BLUE);
  }
  
  if(alarmIsGoingOff && Button_wasPressedNow(&b3)) {
    noTone(BUZZER_PIN);
    alarmIsGoingOff = false; 
  }
  if(!alarmIsGoingOff && alarmIsOn && hour() == hour(alarmTime) && minute() == minute(alarmTime) && second() == second(alarmTime)) {
   tone(BUZZER_PIN, 1000);
   alarmIsGoingOff = true;
  }

  if(mode == ModeLasers) {
    lol += amount; if(lol >= ROW_LENGTH) lol = 0;
    LCDSetLine(60, 64, COL_HEIGHT, lol, GREEN);
    LCDSetLine(60, 64, COL_HEIGHT, ROW_LENGTH-lol, RED);
  }
}



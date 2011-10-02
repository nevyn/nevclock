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

#define BUTTON_S1 3
#define BUTTON_S2 4
#define BUTTON_S3 5
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
  Button_init(&b1, BUTTON_S1);
  Button_init(&b2, BUTTON_S2);
  Button_init(&b3, BUTTON_S3);
  
  mode = ModeTime;
}

void drawClock(tmElements_t forWhen, char *b) {
  char sep = forWhen.Second%2 ? ' ' : ':';
  sprintf(b, "%c %02d%c%02d%c%02d", alarmIsOn?'!':' ', forWhen.Hour, sep, forWhen.Minute, sep, forWhen.Second);
  LCDPutStr(b, 35, 20, WHITE, BLACK);
}

void loop()
{
  char b[64];
  
  if(Button_wasPressedNow(&b3) && !alarmIsGoingOff) {
    mode = (mode + 1) % ModeCount;
    alarmEdit = AlarmEditHour;
    LCDClear(BLACK);
  }
    
//  noTone(50);
//  tone(50, 1000);
//  delayMicroseconds(1000*500);
//  noTone(50);
//  tone(50, 2000);
//  delayMicroseconds(1000*500);
  LCDSetLine(60, 64, COL_HEIGHT, ROW_LENGTH-lol, BLACK);
  LCDSetLine(60, 64, COL_HEIGHT, lol, BLACK);
  
  LCDPutStr(modeNames[mode], 10, 35, WHITE, BLACK);
  
  int forWhen = mode == ModeSetAlarm ? alarmTime : now();
  tmElements_t forWhen2; breakTime(forWhen, forWhen2);
  
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

  
  lol += amount; if(lol >= ROW_LENGTH) lol = 0;
  LCDSetLine(60, 64, COL_HEIGHT, lol, GREEN);
  LCDSetLine(60, 64, COL_HEIGHT, ROW_LENGTH-lol, RED);
}



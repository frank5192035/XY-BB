/*
   -- BB-Ball --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.3 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.5.1 or later version;
     - for iOS 1.4.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>
#include <RemoteXY.h>
#include <Servo.h>

Servo steering; // steering@1-180;

// RemoteXY connection settings
#define REMOTEXY_WIFI_SSID "BB-Ball000"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 8266

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
    {255, 2, 0, 0, 0, 12, 0, 10, 13, 1,
     5, 0, 17, 34, 30, 30, 2, 26, 31};

// this structure defines all the variables and events of your control interface
struct
{
  // input variables
  int8_t joystick_1_x; // =-100..100 x-coordinate joystick position
  int8_t joystick_1_y; // =-100..100 y-coordinate joystick position

  // other variable
  uint8_t connect_flag; // =1 if wire connected, else =0
} RemoteXY;

#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

void setup()
{
  RemoteXY_Init();

  // TODO you setup code
  Serial.begin(115200);

  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(13, LOW); // (LOW, LOW)or(HIGH, HIGH): 馬達不動
  digitalWrite(15, LOW); // (LOW, HIGH): forward  (HIGH, LOW): backward

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  steering.attach(2);
  steering.write(90); // 0: 右, 180: 左
  delay(1000);
}

void loop()
{
  RemoteXY_Handler();
  // TODO you loop code
  // use the RemoteXY structure for data transfer do not call delay(1000);
  int16_t x, y;
  int16_t xSteering;

  x = RemoteXY.joystick_1_x;
  y = RemoteXY.joystick_1_y;

  xSteering = 90 - x / 2; // (140-90-40)
  steering.write(xSteering);

  if (y > 20)
  {
    digitalWrite(13, LOW);  // (LOW, HIGH): forward
    digitalWrite(15, HIGH); //
  }
  else if (y < -20)
  {
    digitalWrite(13, HIGH); // (HIGH, LOW): backward
    digitalWrite(15, LOW);  //
  }
  else
  {
    digitalWrite(13, HIGH); // (LOW, LOW)or(HIGH, HIGH): 馬達不動
    digitalWrite(15, HIGH); //
  }

  Serial.println(xSteering);
}

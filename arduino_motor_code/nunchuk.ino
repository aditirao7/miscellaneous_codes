#include <Wire.h>
#include "Nunchuk.h"
int rf=6;
int rb=3;
int lf=9;
int lb=11;
int ledR, ledL, X;
void setup() {
    Serial.begin(9600);
    Wire.begin();
    pinMode(rf, OUTPUT);
    pinMode(rb, OUTPUT);
    pinMode(lf, OUTPUT);
    pinMode(lb, OUTPUT);
    // nunchuk_init_power(); 
    nunchuk_init();
}

void loop() {

    if (nunchuk_read()) {
        // Work with nunchuk_data
        int x=nunchuk_joystickX_raw();//CENTRE POSITION IS (132, 132)
        int y=nunchuk_joystickY_raw();
        y=constrain(y,34,224);
        x=constrain(x,34,224);
        if(y>142)
        {
          ledR = map(y, 144, 224, 0, 255);
          ledL = map(y, 144, 224, 0, 255);
        }
        else if(y<122)
        {
          ledR = map(y, 122, 34, 0, -255);
          ledL = map(y, 122, 34, 0, -255);
        }
        else
        {
          ledR = 0;
          ledL = 0;
        }
        if(x>142)
        {
          X= map(x, 144, 224, 0, 255);
          ledR = ledR - X;
          ledL = ledL + X;
          if (ledL > 255) 
          {
            ledL = 255;
          }
          if (ledR < -255) 
          {
            ledR = -255;
          }
        }
        else if(x<122)
        {
          X= map(x, 122, 34, 0, 255);
          ledR = ledR + X;
          ledL = ledL - X;
          if (ledR > 255) 
          {
            ledR = 255;
          }
          if (ledL < -255) 
          {
            ledL = -255;
          }
        }
        Serial.print(ledL);
        Serial.print('\t');
        Serial.println(ledR);
        if(ledL<0)
        {
          ledL=-ledL;
          analogWrite(lb,ledL);
          digitalWrite(lf, LOW);
        }
        else
        {
          analogWrite(lf,ledL);
          digitalWrite(lb, LOW);
        }
        if(ledR<0)
        {
          ledR=-ledR;
          analogWrite(rb,ledR);
          digitalWrite(rf, LOW);
        }
        else
        {
          analogWrite(rf,ledR);
          digitalWrite(rb, LOW);
        }
    }
    delay(10);
}

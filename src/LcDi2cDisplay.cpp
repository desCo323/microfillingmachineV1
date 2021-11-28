#include "LcDi2cDisplay.h"
#ifndef LcDi2cDisplay_h
#endif
#define LcDi2cDisplay_h
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Wire.h>
#include "variabelen.h"

//#endif


unsigned long previousMillis2 = 0;  
const long interval = 150;  
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
//Constructor
LcDi2cDisplay::LcDi2cDisplay(){
}

void LcDi2cDisplay::initDisplay(){
   
    lcd.init();
    lcd.backlight();
    lcd.noBacklight();
    lcd.backlight();
   

   
    lcd.setCursor(0, 0);
    lcd.print("Micro Dosis Machine ");
    lcd.setCursor(0, 1);
    lcd.print("  v1");
    lcd.setCursor(0, 2);
    lcd.print(" By Frithjof Ebert 2021");
    //lcd.print(millis() / 1000);
    delay(1000);   
}

void LcDi2cDisplay::printDisplay(String z1, String z2, String z3, String z4){
    unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis2 >= interval) {
    previousMillis2 = currentMillis;
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(z1);


   lcd.setCursor(0, 1);
   lcd.print(z2);


    //if (z3.length() >1){
        lcd.setCursor(0, 2);
        lcd.print(z3);
  //  }
   
   lcd.setCursor(0, 3);
   lcd.print(z4);
  }

}
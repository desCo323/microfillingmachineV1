#include "Arduino.h"
#include "variabelen.h"

String DispZ1= "Zeile1";
String DispZ2= "hallo";
String DispZ3= "Nr3";
String DispZ4="Zeile4";
int test =3;
 int encoderswitchPin=8;
 int endstopPin=4;
 int startPuttonPin=3;
  int systemState=0;
int encoderpinA=6;
int encoderpinB=7;
int rotary =0;
unsigned long dauerProMl=0;


//Schalter
 boolean swEndstop;
 boolean swStartButton;
 boolean swRotaryEncoder;

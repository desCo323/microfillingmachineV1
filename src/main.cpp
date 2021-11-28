#include <Arduino.h>
#include "LcDi2cDisplay.h"
#include "Hardware.h"
#include "variabelen.h"
#include <EEPROM.h>
  LcDi2cDisplay display;
  Hardware hardware;

  int menueItem =0;

  //Kalibriervariabelen
  unsigned long  startzeit=0;
  unsigned long  stopzeit=0;
  unsigned long dauer =0;
  boolean testlauf=false;
  boolean ergebnissanzeige = false;
  boolean speichern = false;
byte by;


   void dauerSpeichern(long lo, int adr){
     Serial.println("in dauerSpeichern " + String(lo));

    for(int i=0;i< 4;i++) {
    by = (lo >> ((3-i)*8)) & 0x000000ff; 
    EEPROM.write(adr+i, by);
  }
} // eepromWriteLong
  
long eepromReadLong(int adr) {
    // long int Wert aus 4 Byte EEPROM lesen
    // Eingabe : adr bis adr+3
    // Ausgabe : long Wert
    // 
    // Matthias Busse 23.5.2014 Version 1.0

    long lo=0;

    for(int i=0;i< 3;i++){
      lo += EEPROM.read(adr+i);
     lo = lo << 8;
    }
   lo += EEPROM.read(adr+3);
    return lo;
} // eepromReadLong
  


  void motorsteuerung(){
  //Motorsteuerung
  if(testlauf ==true && ergebnissanzeige == false){
    display.printDisplay("Kalibrieren laeuft","zum Beenden","nach 50 ml Start","Erneut Druecken");
    //MOTOR AN
  }else{
    //MOTOR AUS
  }
}

 void resetKalVariabelen(){
      startzeit=0;
      stopzeit=0;
      dauer =0;
      testlauf=false;
      ergebnissanzeige = false;
      speichern = false;
      swStartButton=false;
      Serial.println("Variabelen zum Kallibrieren RESETET");
}

void setup() {
 
  hardware.setRotaryZero();
  Serial.begin(9600);
  systemState =0;
  hardware.OneButtonInit();
  dauerProMl = eepromReadLong(0);
  Serial.println("Boot: DauerproMl: " + String(dauerProMl));
  display.initDisplay();
  //Kalibrationswert auslesen und Temp Speichern


}

void loop() {
  hardware.encoder();

hardware.OneButtonLoop();




//Zeige Menü

if (systemState == 0){
  int anzahlMenuepunkte =1;

 if(rotary>anzahlMenuepunkte){hardware.setRotaryZero();}//Encoder auf 0 wenn mehr als Menuepunkte
 if(rotary <0){rotary=anzahlMenuepunkte;}//Bei werten < Menuepunkte zum letzten springen
  switch (rotary)
  {
  case 0:
    display.printDisplay("Menue", "Kalibrieren","","");
    
    if (swRotaryEncoder == true){
      systemState=1;
      resetKalVariabelen();
      swRotaryEncoder = false;
    }
    break;
  case 1:
    display.printDisplay("Menue","Abfuellen","","");

  
  default:
    
    break;
  }
}

//SystemState1: Kalibrieren
if (systemState == 1)
{
  if (startzeit < 1 && testlauf == false)
  {
    display.printDisplay("Kalibrieren:","Start Druecken","NOCHMAL Start ","nach 50ml");
  }
 
  motorsteuerung();

  if(swStartButton == true && startzeit<=0){
    startzeit = millis();
    swStartButton = false;
    testlauf = true;
    Serial.println("KlickStart");
    Serial.println("startin1:");
    Serial.println(startzeit);


  } 

  
//Testlauf beendet durch Klick auf den Startbutton
  if (startzeit>0 && swStartButton == true && testlauf == true){
    //MOTOR AUS
    testlauf = false;
    swStartButton = false;
    if (testlauf == false){
      stopzeit = millis();
      dauer = stopzeit-startzeit;
      ergebnissanzeige = true;
     
     

    }
    
  }

 //Ergebniss anzeigen
  if (ergebnissanzeige == true && testlauf == false && speichern == false)
  {
    Serial.println("Ergebn Anzeige");
   
    display.printDisplay("Kalibrieren BEENDET","50ml in " + String(dauer/1000) +" Sek.", "Speichern= Menue Druecken", "Neustart = Start");
    if(swStartButton == true){
      Serial.println("Neustart d. Messung");
      resetKalVariabelen();
      Serial.println("Neustart");
    }




    
  }
   if(swRotaryEncoder == true && testlauf == false && dauer >0){
    //Speichern

    swRotaryEncoder = false;
     dauerProMl = dauer/50;
        Serial.println("SpeichernKlickt Dauer: " + String(dauer) +"proMl:  "+  String(dauerProMl) );
     display.printDisplay("GESPEICHERT","1ml in " + String(dauerProMl/1000) + " Sek.", "Zurueck zum Menue", "");
     ergebnissanzeige = false;
     delay(1000);
       Serial.println("GESPEICHERT");
   speichern = true;
   dauerSpeichern(dauerProMl,0);
    dauerProMl = eepromReadLong(0);
  Serial.println("Ausgelesen: " + String(dauerProMl));
   Serial.println("DauerGespeichert: " + String(dauerProMl));
   systemState =0;
  }

 
  
}



}




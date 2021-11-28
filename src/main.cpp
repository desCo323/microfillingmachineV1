#include <Arduino.h>
#include "LcDi2cDisplay.h"
#include "Hardware.h"
#include "variabelen.h"
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
  display.initDisplay();
  hardware.setRotaryZero();
  Serial.begin(9600);
  systemState =0;
  hardware.OneButtonInit();
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
   // display.printDisplay("Kalibrieren BEENDET","10ml in",String(dauer/1000),"Sekunden");
    display.printDisplay("Kalibrieren BEENDET","50ml in " + String(dauer/1000) +" Sek.", "Speichern= Menue Druecken", "Neustart = Start");
    if(swStartButton == true){
      Serial.println("Neustart d. Messung");
      resetKalVariabelen();
      Serial.println("Neustart");
    }
   // ergebnissanzeige = false;
   Serial.println("dauer: " + String(dauer));



    
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
   //HIER FEST SPEICHERN
   systemState =0;
  }

 
  
}



}




#include "Hardware.h"
#include <Arduino.h>
#include "variabelen.h"
#include <Encoder.h>
#include "OneButton.h"

 int counter = 0; 
 int aState;
 int aLastState;  
 int Position = 0;
 int Letzte_Position = LOW;
 int n = LOW;


 //OneButton
 OneButton startButton(startPuttonPin, true);
 OneButton endbutton(endstopPin, true);
 OneButton rottaryButton(encoderswitchPin, true);
  
Hardware::Hardware(){

}

/* alt da onebutton übernimmt
void Hardware::hardwareschalterInit(){
    //Endschalter
    pinMode(encoderswitchPin, INPUT_PULLUP);
    pinMode(startPuttonPin, INPUT_PULLUP);
    pinMode(encoderswitchPin,INPUT_PULLUP);
}
*/

void Hardware::OneButtonInit(){
    startButton.attachClick(setStartButton);
    endbutton.attachClick(setEndButton);
    rottaryButton.attachClick(setRotaryButton);


}

static void Hardware::setStartButton(){ swStartButton = true;}
static void Hardware::setEndButton(){ swEndstop = true;}
static void Hardware::setRotaryButton(){ swRotaryEncoder = true;}

void Hardware::OneButtonLoop(){
    startButton.tick();
    endbutton.tick();
    rottaryButton.tick();
    
}


void Hardware::schalterKontrollieren(){
    int readEndstop = digitalRead(endstopPin);
    int readStartButtonpin = digitalRead(startPuttonPin);
    int readEncoderSwitchPin = digitalRead(encoderswitchPin);

    if(readEncoderSwitchPin == LOW){
      //  DispZ1 = "EncoderKlick";
        swRotaryEncoder =true;
    }else{
      //  DispZ1 = "Encoder High";
        swRotaryEncoder = false;
    }

    if(readStartButtonpin == LOW){
     //   DispZ2 = "StartKlick";
        swStartButton = true;
        
    }else{
      //  DispZ2 = "Start High";
        swStartButton = false;
    }
    
    if(readEndstop == LOW){
    //    DispZ3 = "EndKlick";
        swEndstop = true;
    }else{
     //   DispZ3 = "End High";
        swEndstop = false;
    }
    
}

void Hardware::encoder(){

  /*
 aState = digitalRead(encoderpinA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(encoderpinB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
    rotary = counter;
    //// Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
}
*/
  n = digitalRead(encoderpinA); //CLK
  if ((Letzte_Position == LOW) && (n == HIGH)) {
    if (digitalRead(encoderpinB) == LOW) {
      rotary++;
    } else {
      rotary--;
    }
    //rotary=Position;
    Serial.print (Position);
    Serial.print ("|");
    Serial.println (rotary);
  }
Letzte_Position = n;


}
void Hardware::setRotaryZero(){
    rotary =0;
    Serial.println ("Rot =0" + rotary);
}

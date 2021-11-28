#ifndef Lcdi2cDisplay_h
#define Lcdi2cDisplay_h
#include <LiquidCrystal_I2C.h>
#endif
#include <Arduino.h>

class LcDi2cDisplay{
public:
    LcDi2cDisplay();
    /** initDisplay
     * @brief Iniziiert das Display und gibt den Bootscreen aus. Muss in der Setup() aufgerufen werden.
     * 
     */
     void initDisplay();
    void printDisplay(String z1, String z2, String z3, String z4);
};

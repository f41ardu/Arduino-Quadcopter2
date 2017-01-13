/*
 * Devlopment Branch
 */ 
// http://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Klassen

#ifndef PinClass2_H
#define PinClass2_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"  // for digitalRead, digitalWrite, etc
#else
#include "WProgram.h"
#endif 
//#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"

class PinClass2
{
  public:                             // öffentlich
    PinClass2();                       // der Default-Konstruktor
    PinClass2(int a);                  // weiterer Konstruktor mit Parameter
    PinClass2(int a,unsigned int OnTime, unsigned int OffTime);  
    //   PinClass2(const LED& a);      // Copy-Konstruktor wird nicht benötigt
       ~PinClass2();                   // Class Destruktor

    void init(int pin);               // einen PIN mit einem (Default-) Parameter LED Initialisieresn
    void on();                        // einen PIN einschalten
    void off();                       // einen PIN ausschalten
    void blink(int intervall);        // einen PIN für die länge von intervall (ms) ein- und ausschalten
    void fade(int value);             // eine Spannung (0 .. 5Volt/255) am PIN ausgeben
    void timechange(int OnTime, int OffTime); 
    void toggle();                    // PIN Zustand umschalten (ON/OFF, OFF/ON) 
    void flash();                     // PIN ein und auschalten (OnTime, OffTime) 

  private:                            // privat
     bool _status; 
    int _pin;
    unsigned int _previousMillis, _currentMillis, _OnTime, _OffTime;

};

#endif // PinClass2



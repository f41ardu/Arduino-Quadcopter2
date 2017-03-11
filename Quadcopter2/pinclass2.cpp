/* 
 *Devlopment Branch
 */ 
// http://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Klassen

#include "pinclass2.h"

PinClass2::PinClass2(): // Constructor
  _pin(0), _status(0)
{
  //leerer Constructor;
}

PinClass2::PinClass2(int a): // Constructor mit Initialisierung
  _pin(a), _status(0)
{
  init(_pin);
}

PinClass2::PinClass2(int pin, unsigned int OnTime, unsigned int OffTime): // Contructor
  _OnTime(OnTime), _OffTime(OffTime), _pin(pin)
{
  init(_pin);
  _previousMillis = millis();
 off();
}

PinClass2::~PinClass2() // Destructor
{
}

void PinClass2::init(int pin) // LED intialsieren
{
  _pin = pin;                   // speichert den LED Pin in der privaten Variable _led
  pinMode(_pin, OUTPUT);
}
void PinClass2::on() // LED ein
{
  _status = true;
  digitalWrite(_pin, HIGH); //set the pin HIGH and thus turn LED on
}

void PinClass2::off() // LED aus
{
  _status = false;
  digitalWrite(_pin, LOW); //set the pin HIGH and thus turn LED off
}

void PinClass2::blink(int intervall) // LED einmal intervall ms blinken lassen
{
  on();
  delay(intervall / 2);
  off();
  delay(intervall / 2);
}

void PinClass2::fade(int value) // LED Helligkeit setzen
{
  analogWrite(_pin, value);
}

void PinClass2::toggle()
{
  _status ? off() : on();
}

void PinClass2::timechange(int OnTime, int OffTime) // 
{
  _OnTime=OnTime;
  _OffTime=OffTime;
}

void PinClass2::flash() {
  // check to see if it's time to change the state of the LED
  if ((_currentMillis - _previousMillis >= _OnTime))
  {
    toggle();  // Turn it off
    _previousMillis = _currentMillis;  // Remember the time
  }
  else if ((_currentMillis - _previousMillis >= _OffTime))
  {
    toggle();  // turn it on
    _previousMillis = _currentMillis;   // Remember the time
  }
  _currentMillis = millis();
}



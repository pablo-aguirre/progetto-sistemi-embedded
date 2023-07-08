#include "Pump.h"
#include <Arduino.h>

Pump::Pump(int pin) {
  this -> pin = pin;
}

void Pump::begin() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); // da sistemare quando cambiamo/sistemiamo il relè
}

void Pump::activate() {
  digitalWrite(pin, LOW);
}

void Pump::activateFor(int seconds) {
  activate();
  delay(seconds * 1000);
  deactivate();
}

void Pump::deactivate() {
  digitalWrite(pin, HIGH);
}




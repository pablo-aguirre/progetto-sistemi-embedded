#include "Led.h"
#include <Arduino.h>

Led::Led(int pin) {
  this -> pin = pin;
  this -> state = false;
}

void Led::begin() {
  pinMode(pin, OUTPUT);
}

void Led::on() {
  digitalWrite(pin, HIGH);
  state = true;
}

void Led::off() {
  digitalWrite(pin, LOW);
  state = false;
}

void Led::toggle() {
  if (state) off();
  else on();
}

void Led::blink(int duration) {
  on();
  delay(duration);
  off();
  delay(duration);
}

bool Led::isOn() {
  return state;
}

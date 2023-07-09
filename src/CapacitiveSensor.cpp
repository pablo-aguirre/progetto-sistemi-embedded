#include "CapacitiveSensor.h"
#include <Arduino.h>

CapacitiveSensor::CapacitiveSensor(int pin, int wetLevel, int dryLevel) {
  this->pin = pin;
  this->wetLevel = wetLevel;
  this->dryLevel = dryLevel;
  this->level = 0;
}

void CapacitiveSensor::begin() {
  level = analogRead(pin);
}

int CapacitiveSensor::getLevel() {
  return analogRead(pin);
}

bool CapacitiveSensor::isUnderThreshold(int threshold) {
  return this->getLevel() < threshold;
}

int CapacitiveSensor::getLevelPercentage() {
  return map(this->getLevel(), 0, 1023, 0, 100);
}

bool CapacitiveSensor::isWet() {
  return this->getLevel() < wetLevel;
}

bool CapacitiveSensor::isDry() {
  return this->getLevel() > dryLevel;
}
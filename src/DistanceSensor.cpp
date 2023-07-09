#include "DistanceSensor.h"
#include <Arduino.h>

DistanceSensor::DistanceSensor(int triggerPin, int echoPin) {
  this -> triggerPin = triggerPin;
  this -> echoPin = echoPin;
}

void DistanceSensor::begin() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float DistanceSensor::getDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2;
  return (distance > 400 || distance < 2) ? NULL : distance;
}

bool DistanceSensor::isObjectDetected(float thresholdDistance) {
  float distance = getDistance();
  return (distance < thresholdDistance);
}

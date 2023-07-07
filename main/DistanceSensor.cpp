#include "DistanceSensor.h"
#include <Arduino.h>

DistanceSensor::Ultrasonic(int triggerPin, int echoPin) {
  triggerPin = triggerPin;
  echoPin = echoPin;
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
  return distance;
}

bool DistanceSensor::isObjectDetected(float thresholdDistance) {
  float distance = getDistance();
  return (distance < thresholdDistance);
}

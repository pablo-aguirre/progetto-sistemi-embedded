#include "LedRGB.h"

LedRGB::LedRGB(byte redPin, byte greenPin, byte bluePin){
    this -> redPin = redPin;
    this -> greenPin = greenPin;
    this -> bluePin = bluePin;
}

void LedRGB::setColor(int red, int green, int blue){
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}
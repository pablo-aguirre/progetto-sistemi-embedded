#ifndef LED_RGB_H
#define LED_RGB_H

#include <Arduino.h>

class LedRGB {
    private:
        byte redPin, greenPin, bluePin;
    public:
        LedRGB(byte redPin, byte greenPin, byte bluePin);
        
        void setColor(int red, int blue, int green);

        void blink(int);
};

#endif
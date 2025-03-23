#ifndef PINOUTS_H
#define PINOUTS_H

#include <Arduino.h>

class Pinouts {
public:
    static void init();
    static const int buttonPins[3];
    static const int screenAddress;
    static const int pumpPins[4];
    static const int sensorPins[4];
};

#endif // PINOUTS_H

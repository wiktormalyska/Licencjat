#include "Pinouts.h"


void Pinouts::init(){
    for (int i = 0; i < 3; i++) {
        pinMode(buttonPins[i], INPUT);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(pumpPins[i], OUTPUT);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(sensorPins[i], INPUT_PULLDOWN);
    }
}

const int Pinouts::buttonPins[3] = {2, 4, 5};
const int Pinouts::screenAddress = 0x3C;
const int Pinouts::pumpPins[4] = {14, 15, 18, 19};
const int Pinouts::sensorPins[4] = {32, 33, 35, 34};

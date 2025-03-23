#ifndef BUTTONSMANAGER_H
#define BUTTONSMANAGER_H

#include "Pinouts.h"
#include <Arduino.h>

class ButtonsManager {
public:
    static bool getButtonValue(int num);
private:
    static int _buttonPressed[3];
};

#endif
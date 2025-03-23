#include "ButtonsManager.h"

int ButtonsManager::_buttonPressed[3] = {0,0,0};

bool ButtonsManager::getButtonValue(int num){
    int val = digitalRead(Pinouts::buttonPins[num]);
    if (val == 1 && ButtonsManager::_buttonPressed[num] != 1){
      ButtonsManager::_buttonPressed[num] = 1;
      return true;
    }
    if (val == 0 && ButtonsManager::_buttonPressed[num] != 0){
      ButtonsManager::_buttonPressed[num] = 0;
    }
    return false;
}
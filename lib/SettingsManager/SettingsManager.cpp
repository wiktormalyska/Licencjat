#include <SettingsManager.h>

int SettingsManager::pumpActivationValues[MAX_PUMPS] = {50, 50, 50, 50};

int SettingsManager::readPumpSettings(int pumpIndex) {
    return pumpActivationValues[pumpIndex];
}

void SettingsManager::writePumpSettings(int pumpIndex, int value){
    if (value < 0 || value > 100) {
        value = 50;
    }
    pumpActivationValues[pumpIndex] = value;
}
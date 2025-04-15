#include <SettingsManager.h>

char* SettingsManager::nameSpace = "AutonomicPlantWatering";

Preferences SettingsManager::preferences;

float SettingsManager::readPumpSettings(int pumpNumber){
    preferences.begin(nameSpace, false);
    preferences.getInt("pump_"+pumpNumber, 0);
    preferences.end();
}

void SettingsManager::writePumpSettings(int pumpNumber, float value){
    preferences.begin(nameSpace, false);
    preferences.putInt("pump_"+pumpNumber, value);
    preferences.end();
}
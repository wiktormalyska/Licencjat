#include <SettingsManager.h>

char* SettingsManager::nameSpace = "AutonomicPlantWatering";

Preferences SettingsManager::preferences;

float SettingsManager::readPumpSettings(int pumpNumber){
    preferences.begin(nameSpace, false);
    preferences.putString("pump_"+pumpNumber, String(pumpNumber));
    preferences.end();
}

void SettingsManager::writePumpSettings(int pumpNumber, float value){
    preferences.begin(nameSpace, false);
    preferences.putString("pump_"+pumpNumber, String(pumpNumber));
    preferences.end();
    
    
}
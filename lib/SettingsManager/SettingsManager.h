#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <string.h>
#include <Preferences.h>

class SettingsManager {
private:
    static char* nameSpace;
    static Preferences preferences;
public:
    static float readPumpSettings(int pumpNumber);
    static void writePumpSettings(int pumpNumber, float value);
};

#endif
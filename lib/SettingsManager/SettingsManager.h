#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#define MAX_PUMPS 4
#include <string.h>

class SettingsManager {
public:
    static int readPumpSettings(int pumpIndex);
    static void writePumpSettings(int pumpIndex, int value);
private:
    static int pumpActivationValues[MAX_PUMPS];
};

#endif
#ifndef PUMPSMANAGER_H
#define PUMPSMANAGER_H

#include <Pinouts.h>
#include <SettingsManager.h>
#include <SensorsManager.h>

class PumpsManager {
private:
    static const int PUMP_ACTIVATION_TIME = 10000;   // Czas działania pompy
    static const int PUMP_TIMEOUT = 5000;          // Timeout pompy
    static const int CHECK_INTERVAL = 5000;        // Częstotliwość sprawdzania
    
    static unsigned long lastCheckTime;              // Czas ostatniego sprawdzenia
    static unsigned long pumpStartTimes[MAX_PUMPS];  // Czasy uruchomienia pomp
    static unsigned long pumpTimeouts[MAX_PUMPS];    // Czasy timeout dla pomp
    static bool pumpActive[MAX_PUMPS];               // Stan pomp (aktywna/nieaktywna)
public:
    static void init();
    static void update();
    static void activatePump(int pumpIndex);
    static void deactivatePump(int pumpIndex);
    static bool isPumpActive(int pumpIndex);
    static void checkAndControlPumps();
};

#endif
#include <PumpsManager.h>

unsigned long PumpsManager::lastCheckTime = 0;
unsigned long PumpsManager::pumpStartTimes[MAX_PUMPS] = {0};
unsigned long PumpsManager::pumpTimeouts[MAX_PUMPS] = {0};
bool PumpsManager::pumpActive[MAX_PUMPS] = {false, false, false, false};

void PumpsManager::init() {
    // Inicjalizacja zmiennych czasowych
    lastCheckTime = millis();
    for (int i = 0; i < MAX_PUMPS; i++) {
        pumpStartTimes[i] = 0;
        pumpTimeouts[i] = 0;
        pumpActive[i] = false;
    }
}

void PumpsManager::update() {
    unsigned long currentTime = millis();
    
    // Sprawdź czy któraś z pomp powinna zostać wyłączona
    for (int i = 0; i < MAX_PUMPS; i++) {
        if (pumpActive[i] && (currentTime - pumpStartTimes[i] >= PUMP_ACTIVATION_TIME)) {
            Serial.print("Wyłączam pompę ");
            Serial.print(i);
            Serial.print(" po ");
            Serial.print(PUMP_ACTIVATION_TIME / 1000);
            Serial.println(" sekundach działania");
            
            deactivatePump(i);
            pumpTimeouts[i] = currentTime;
            
            Serial.print("Rozpoczynam timeout pompy ");
            Serial.print(i);
            Serial.print(" na ");
            Serial.print(PUMP_TIMEOUT / 1000);
            Serial.println(" sekund");
        }
    }
    
    // Sprawdź czy nadszedł czas na sprawdzenie sensorów
    if (currentTime - lastCheckTime >= CHECK_INTERVAL) {
        Serial.print("==== Sprawdzanie sensorów (czas: ");
        Serial.print(currentTime / 1000);
        Serial.println("s) ====");
        checkAndControlPumps();
        lastCheckTime = currentTime;
    }
}

void PumpsManager::activatePump(int pumpIndex) {
    if (pumpIndex >= 0 && pumpIndex < MAX_PUMPS) {
        digitalWrite(Pinouts::pumpPins[pumpIndex], HIGH);
        pumpActive[pumpIndex] = true;
        pumpStartTimes[pumpIndex] = millis();
        
        Serial.print("POMPA ");
        Serial.print(pumpIndex);
        Serial.println(" WŁĄCZONA");
    }
}

void PumpsManager::deactivatePump(int pumpIndex) {
    if (pumpIndex >= 0 && pumpIndex < MAX_PUMPS) {
        digitalWrite(Pinouts::pumpPins[pumpIndex], LOW);
        pumpActive[pumpIndex] = false;
        
        Serial.print("POMPA ");
        Serial.print(pumpIndex);
        Serial.println(" WYŁĄCZONA");
    }
}

bool PumpsManager::isPumpActive(int pumpIndex) {
    if (pumpIndex >= 0 && pumpIndex < MAX_PUMPS) {
        return pumpActive[pumpIndex];
    }
    return false;
}

void PumpsManager::checkAndControlPumps() {
    unsigned long currentTime = millis();
    
    // Sprawdź każdą pompę
    for (int i = 0; i < MAX_PUMPS; i++) {
        Serial.print("Sprawdzam pompę ");
        Serial.print(i);
        Serial.print(": ");
        
        // Sprawdź, czy pompa nie jest w czasie timeout
        if (currentTime - pumpTimeouts[i] < PUMP_TIMEOUT) {
            int remainingTimeout = (PUMP_TIMEOUT - (currentTime - pumpTimeouts[i])) / 1000;
            Serial.print("W czasie timeout (pozostało ");
            Serial.print(remainingTimeout);
            Serial.println("s)");
            continue; // Pompa w czasie timeout, przejdź do następnej
        }
        
        // Sprawdź, czy pompa nie jest już aktywna
        if (pumpActive[i]) {
            int activeTime = (currentTime - pumpStartTimes[i]) / 1000;
            Serial.print("Już aktywna (od ");
            Serial.print(activeTime);
            Serial.println("s)");
            continue; // Pompa już aktywna, przejdź do następnej
        }
        
        // Pobierz wartość z sensora i wartość progową
        int sensorValue = SensorsManager::getSensorValue(i);
        int threshold = SettingsManager::readPumpSettings(i);
        
        Serial.print("Wartość sensora: ");
        Serial.print(sensorValue);
        Serial.print("%, próg: ");
        Serial.print(threshold);
        Serial.print("% - ");
        
        // Jeśli wartość sensora jest poniżej progu aktywacji, włącz pompę
        if (sensorValue < threshold) {
            Serial.println("URUCHAMIAM POMPĘ!");
            activatePump(i);
        } else {
            Serial.println("poziom wilgotności w normie");
        }
    }
    Serial.println("============================");
}
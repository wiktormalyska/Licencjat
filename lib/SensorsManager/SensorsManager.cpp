#include "SensorsManager.h"

int SensorsManager::getSensorValue(int sensorIndex){

    return (analogRead(Pinouts::sensorPins[sensorIndex]) / 4095.0) * 100;
}
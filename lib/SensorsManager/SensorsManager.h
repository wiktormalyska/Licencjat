#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <Pinouts.h>

class SensorsManager {
public:
    static float getSensorValue(int sensorIndex);
};

#endif
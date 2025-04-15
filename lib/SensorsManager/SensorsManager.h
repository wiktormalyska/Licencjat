#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <Pinouts.h>

class SensorsManager {
public:
    static int getSensorValue(int sensorIndex);
};

#endif
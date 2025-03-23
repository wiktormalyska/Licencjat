#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <U8g2lib.h>
#include "I2CScanner.h"
#include "SensorsManager.h"

class ScreenManager {
public:
    static void init();
    static void showStartupScreen();
    static void clearScreen();
    static void displayMainScreen();
    static U8G2_SH1106_128X64_NONAME_F_HW_I2C _u8g2;
private:
    static I2CScanner _scanner;
    static void checkScreenConnection();
};

#endif
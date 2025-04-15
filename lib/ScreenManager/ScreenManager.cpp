#include "ScreenManager.h"
#include "SensorsManager.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C ScreenManager::_u8g2 = U8G2_SH1106_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
I2CScanner ScreenManager::_scanner;
MenuManager ScreenManager::_menuManager;
ScreenManagerState ScreenManager::_state = SCREEN_STARTUP;

void ScreenManager::init() {

    _scanner.Init();
    checkScreenConnection();
    _u8g2.begin();
}

void ScreenManager::showStartupScreen() {
    _u8g2.clearBuffer();
    _u8g2.setFont(u8g2_font_helvR14_tf);
    _u8g2.drawStr(0, 24, "Autonomic");
    _u8g2.drawStr(0, 48, "Plant Watering");
    _u8g2.sendBuffer();
    delay(2000);
}

void ScreenManager::clearScreen() {
    _u8g2.clearBuffer();
}

void ScreenManager::displayMainScreen() {
    _u8g2.clearBuffer();
    _u8g2.drawLine(32, 0, 32, 63);
    _u8g2.drawLine(64, 0, 64, 63);
    _u8g2.drawLine(96, 0, 96, 63);

    _u8g2.setFont(u8g2_font_6x10_tf);
    _u8g2.drawStr(10, 10, "01");
    _u8g2.drawStr(42, 10, "02");
    _u8g2.drawStr(74, 10, "03");
    _u8g2.drawStr(106, 10, "04");

    char buf[4][10];  

    for (int i = 0; i < 4; i++) {
        int sensorValue = SensorsManager::getSensorValue(i);
        if (sensorValue == 0) {
            strcpy(buf[i], "00");
        } else {
            dtostrf(sensorValue, 6, 0, buf[i]);

            char* p = buf[i];
            while (*p == ' ') p++;
            
            if (p != buf[i]) {
                memmove(buf[i], p, strlen(p) + 1);
            }
        }

    }
    
    int sectorWidth = 32;
    int sectorCenters[4] = {16, 48, 80, 112};
    
    for (int i = 0; i < 4; i++) {
        int textWidth = _u8g2.getStrWidth(buf[i]);
        int x = sectorCenters[i] - (textWidth / 2);
        _u8g2.drawStr(x, 40, buf[i]);
    }

    _u8g2.sendBuffer();
}

void ScreenManager::checkScreenConnection() {
    if (!_scanner.Check()) {
      delay(5000);
      checkScreenConnection();
    }
    Serial.print("Screen detected!");
}

void ScreenManager::displayMenu() {
    _menuManager.displayMenu();
}
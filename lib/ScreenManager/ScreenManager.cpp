#include "ScreenManager.h"
#include "SensorsManager.h"
#include "SettingsManager.h"

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

    // Podziały ekranu
    _u8g2.drawLine(32, 0, 32, 63);
    _u8g2.drawLine(64, 0, 64, 63);
    _u8g2.drawLine(96, 0, 96, 63);

    // Mała czcionka do opisów
    _u8g2.setFont(u8g2_font_6x10_tf);
    _u8g2.drawStr(10, 10, "01");
    _u8g2.drawStr(42, 10, "02");
    _u8g2.drawStr(74, 10, "03");
    _u8g2.drawStr(106, 10, "04");

    int sectorCenters[4] = {16, 48, 80, 112};
    int sectorWidth = 32;
    int maxHeight = 40;
    int barBottom = 60;
    int barWidth = 8;

    for (int i = 0; i < 4; i++) {
        // Odczyt czujnika
        int sensorValue = SensorsManager::getSensorValue(i);
        if (sensorValue < 0) sensorValue = 0;
        if (sensorValue > 100) sensorValue = 100;

        // Próg aktywacji
        int threshold = SettingsManager::readPumpSettings(i);
        if (threshold < 0) threshold = 0;
        if (threshold > 100) threshold = 100;

        // Przeskalowanie wartości
        int barHeight = (sensorValue * maxHeight) / 100;
        int thresholdY = barBottom - (threshold * maxHeight) / 100;

        // Pozycje
        int barX = sectorCenters[i] - (barWidth / 2);
        int barY = barBottom - barHeight;

        // Rysowanie słupka
        _u8g2.drawBox(barX, barY, barWidth, barHeight);

        _u8g2.drawFrame(barX, barBottom - maxHeight, barWidth, maxHeight);

        // Rysowanie kreski progu
        _u8g2.drawLine(barX - 2, thresholdY, barX + barWidth + 2, thresholdY);
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
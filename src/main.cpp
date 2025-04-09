#include <string>
#include <Wire.h>
#include <U8g2lib.h>
#include <I2CScanner.h>
#include "ScreenManager.h"
#include "Pinouts.h"
#include "ButtonsManager.h"

ScreenManager screenManager;
Pinouts pinouts;
ButtonsManager buttonsManager;




void setup() {
    Serial.begin(9600);
    while (!Serial) {};

    ScreenManager::init();
    Pinouts::init();

    ScreenManager::_state = ScreenManagerState::STARTUP;
    ScreenManager::showStartupScreen();
}

void loop() {
    switch (ScreenManager::_state) {
    case ScreenManagerState::MAIN:
        ScreenManager::displayMainScreen();
        if (ButtonsManager::getButtonValue(1)) {
            ScreenManager::_state = ScreenManagerState::MENU;
        }
        break;
    case ScreenManagerState::MENU:
        ScreenManager::displayMenu();
        break;

}
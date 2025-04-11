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

int menuPosition = 0;



void setup() {
    Serial.begin(9600);
    while (!Serial) {};

    ScreenManager::init();
    Pinouts::init();

    ScreenManager::_state = ScreenManagerState::SCREEN_STARTUP;
    ScreenManager::showStartupScreen();
    ScreenManager::_state = ScreenManagerState::SCREEN_MAIN;
}

void loop() {
    switch (ScreenManager::_state) {
    case ScreenManagerState::SCREEN_MAIN:
        ScreenManager::displayMainScreen();
        if (ButtonsManager::getButtonValue(1)) {
            ScreenManager::_state = ScreenManagerState::SCREEN_MENU;
        }
        break;
    case ScreenManagerState::SCREEN_MENU:
        ScreenManager::displayMenu();
        break;
    }
}
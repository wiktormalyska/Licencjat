#include "MenuManager.h"
#include <ButtonsManager.h>
#include <ScreenManager.h>
#include <SensorsManager.h>
#include <SettingsManager.h>

MenuManagerState MenuManager::state = MENU;
ButtonsManager MenuManager::_buttonsManager;
int MenuManager::menuPosition = 0;
int MenuManager::pumpActivationValues[4] = {50, 50, 50, 50};

bool MenuManager::setMenuState(MenuManagerState state){
    MenuManager::state = state;
    return true;
}
void MenuManager::displayMenu(){
    ScreenManager _screenManager;
    U8G2_SH1106_128X64_NONAME_F_HW_I2C _u8g2 = _screenManager._u8g2;

    switch (MenuManager::state){

        case MENU:
            if (ButtonsManager::getButtonValue(0)){
                menuPosition--;
                if (menuPosition < 0){
                    menuPosition = 4;
                }
            } else if (ButtonsManager::getButtonValue(2)){
                menuPosition++;
                if (menuPosition > 4){
                    menuPosition = 0;
                }
            }
            showMenuSelection(menuPosition);            
            break;
        case PUMP1:
            showPumpMenu(1);
            break;
        case PUMP2:
            showPumpMenu(2);
            break;
        case PUMP3:
            showPumpMenu(3);
            break;
        case PUMP4:
            showPumpMenu(4);
            break;
    }
}

void MenuManager::showMenuSelection(int menuPosition){
    U8G2_SH1106_128X64_NONAME_F_HW_I2C _u8g2 = ScreenManager::_u8g2;

    int screenWidth = _u8g2.getWidth();
    int textWidth = _u8g2.getStrWidth("Menu");
    int xPosition = (screenWidth - textWidth) / 2;

    _u8g2.clearBuffer();
    _u8g2.setFont(u8g2_font_tiny5_tf);
    _u8g2.drawStr(xPosition, 10, "Menu");

    const char* menuOptions[] = {"Pump 1", "Pump 2", "Pump 3", "Pump 4", "Back"};
    
    for (int i = 0; i < 5; i++) {
        int yPos = 20 + i * 10;
        if (i == menuPosition) {
            _u8g2.drawStr(0, yPos, "> ");
        }
        _u8g2.drawStr(10, yPos, menuOptions[i]);
    }

    if (ButtonsManager::getButtonValue(1)) {
        switch (menuPosition) {
            case 0:
                MenuManager::state = PUMP1;
                break;
            case 1:
                MenuManager::state = PUMP2;
                break;
            case 2:
                MenuManager::state = PUMP3;
                break;
            case 3:
                MenuManager::state = PUMP4;
                break;
            case 4:
                ScreenManager::_state = SCREEN_MAIN;
                MenuManager::state = MENU;
                menuPosition = 0;
                break;
        }
    }

    _u8g2.sendBuffer();
}

void MenuManager::showPumpMenu(int pumpNumber){
    U8G2_SH1106_128X64_NONAME_F_HW_I2C _u8g2 = ScreenManager::_u8g2;
    _u8g2.clearBuffer();
    _u8g2.setFont(u8g2_font_5x7_tf);
    int screenWidth = _u8g2.getWidth();

    static bool firstEntry = true;
    static int activationValue = 50;
    
    if (firstEntry) {
        activationValue = loadActivationValue(pumpNumber - 1);
        firstEntry = false;
    }

    if (ButtonsManager::getButtonValue(0)){
        activationValue -= 5;
        if (activationValue < 0) activationValue = 0;
    } else if (ButtonsManager::getButtonValue(2)){
        activationValue += 5;
        if (activationValue > 100) activationValue = 100;
    }

    char buf[20];
    snprintf(buf, sizeof(buf), "Pump %d", pumpNumber);
    drawCenteredText(_u8g2, buf, 10);

    float sensorValue = SensorsManager::getSensorValue(pumpNumber - 1);
    char valueBuf[20];
    snprintf(valueBuf, sizeof(valueBuf), "Value: %.2f", sensorValue);
    drawCenteredText(_u8g2, valueBuf, 25);

    char activationBuf[20];
    snprintf(activationBuf, sizeof(activationBuf), "Activation: %d%%", activationValue);
    drawCenteredText(_u8g2, activationBuf, 35);

    int frameWidth = 100;
    int frameHeight = 10;
    int frameX = (screenWidth - 100) / 2;
    int frameY = 40;
    _u8g2.drawFrame(frameX, frameY, frameWidth, frameHeight);

    int fillWidth = (int)(sensorValue * frameWidth / 100.0);
    if (fillWidth > frameWidth) fillWidth = frameWidth;
    if (fillWidth < 0) fillWidth = 0;
    _u8g2.drawBox(frameX, frameY, fillWidth, frameHeight);

    int markerX = frameX + (int)(activationValue * frameWidth / 100.0);
    _u8g2.drawLine(markerX, frameY - 2, markerX, frameY + frameHeight + 2);

    drawCenteredText(_u8g2, "<apply>", 62);

    _u8g2.sendBuffer();

    if (_buttonsManager.getButtonValue(1)){
        saveActivationValue(pumpNumber - 1, activationValue);
        MenuManager::state = MENU;
        firstEntry = true;
    }
}

void MenuManager::drawCenteredText(U8G2_SH1106_128X64_NONAME_F_HW_I2C &u8g2, const char* text, int yPos) {
    int screenWidth = u8g2.getWidth();
    int textWidth = u8g2.getStrWidth(text);
    int xPosition = (screenWidth - textWidth) / 2;
    u8g2.drawStr(xPosition, yPos, text);
}

void MenuManager::saveActivationValue(int pumpIndex, int value) {
    SettingsManager::writePumpSettings(pumpIndex, value);
    pumpActivationValues[pumpIndex] = value;
}

int MenuManager::loadActivationValue(int pumpIndex) {
    return SettingsManager::readPumpSettings(pumpIndex);
}
#include "MenuManager.h"
#include <ButtonsManager.h>
#include <ScreenManager.h>

MenuManagerState MenuManager::state = MENU;
int MenuManager::menuPosition = 0;
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
    _u8g2.setFont(u8g2_font_helvR14_tf);
    _u8g2.drawStr(0, 10, "Pump "+pumpNumber);
    _u8g2.sendBuffer();
}
#include "MenuManager.h"


MenuManagerState MenuManager::state = MENU;
bool MenuManager::setMenuState(MenuManagerState state){
    MenuManager::state = state;
    return true;
}
void MenuManager::displayMenu(){
    ScreenManager _screenManager;
    U8G2_SH1106_128X64_NONAME_F_HW_I2C _u8g2 = _screenManager._u8g2;
    switch (MenuManager::state){

        case MENU:
            _u8g2.clearBuffer();
            _u8g2.setFont(u8g2_font_helvR14_tf);
            _u8g2.drawStr(0, 24, "Menu");
            _u8g2.sendBuffer();
            break;
        case PUMP1:
            _u8g2.clearBuffer();
            _u8g2.setFont(u8g2_font_helvR14_tf);
            _u8g2.drawStr(0, 24, "Pump 1");
            _u8g2.sendBuffer();
            break;
        case PUMP2:
            _u8g2.clearBuffer();
            _u8g2.setFont(u8g2_font_helvR14_tf);
            _u8g2.drawStr(0, 24, "Pump 2");
            _u8g2.sendBuffer();
            break;
        case PUMP3:
            _u8g2.clearBuffer();
            _u8g2.setFont(u8g2_font_helvR14_tf);
            _u8g2.drawStr(0, 24, "Pump 3");
            _u8g2.sendBuffer();
            break;
        case PUMP4:
            _u8g2.clearBuffer();
            _u8g2.setFont(u8g2_font_helvR14_tf);
            _u8g2.drawStr(0, 24, "Pump 4");
            _u8g2.sendBuffer();
            break;
    }
}

MenuManagerState MenuManager::getMenuState(){

}
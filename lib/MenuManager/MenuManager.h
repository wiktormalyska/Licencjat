#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <U8g2lib.h>
#include <ButtonsManager.h>

enum MenuManagerState
{
    MENU, PUMP1, PUMP2, PUMP3, PUMP4
};


class MenuManager {
public:
    static MenuManagerState getMenuState();
    static bool setMenuState(MenuManagerState state);
    static void displayMenu();
    static MenuManagerState state;
private:
    static ButtonsManager _buttonsManager;
    static int menuPosition;
    static void showMenuSelection(int menuPosition);
    static void showPumpMenu(int pumpNumber);
    static void drawCenteredText(U8G2_SH1106_128X64_NONAME_F_HW_I2C &u8g2, const char* text, int yPos);
};

#endif
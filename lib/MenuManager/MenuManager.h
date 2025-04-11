#ifndef MENUMANAGER_H
#define MENUMANAGER_H
#include <U8g2lib.h>

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
    static int menuPosition;
    static void showMenuSelection(int menuPosition);
    static void showPumpMenu(int pumpNumber);
};

#endif
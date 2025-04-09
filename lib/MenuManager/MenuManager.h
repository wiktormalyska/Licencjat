#ifndef MENUMANAGER_H
#define MENUMANAGER_H
#include "ScreenManager.h"

enum MenuManagerState
{
    MENU, PUMP1, PUMP2, PUMP3, PUMP4
};


class MenuManager {
public:
    static MenuManagerState getMenuState();
    static bool setMenuState(MenuManagerState state);
    static void displayMenu();
private:
    static MenuManagerState state;
};

#endif
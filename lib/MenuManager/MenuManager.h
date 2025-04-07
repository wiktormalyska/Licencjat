#ifndef MENUMANAGER_H
#define MENUMANAGER_H

enum MenuManagerState
{
    MENU, PUMP1, PUMP2, PUMP3, PUMP4
};


class MenuManager {
public:
    static MenuManagerState getMenuState();
    static bool setMenuState(MenuManagerState state);
private:
    static MenuManagerState state;
};

#endif
#ifndef MENU_H
#define MENU_H
#include "CommonFunc.h"
#include "LTexture.h"
class Menu : public LTexture
{
public:
    Menu();
    ~Menu();
    void loadMenu();
    void renderMenu();
};
#endif // MENU_H

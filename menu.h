#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include "configuration.h"
#include "menubutton.h"
#include "map.h"
#include <QDebug>

class Menu : public QGraphicsScene
{
public:
    Menu();
    ~Menu();

    QList<MenuButton *> getButtonList() const;

    MenuButton *getQuitBtn() const;

private:
    QList<MenuButton *> buttonList;
    MenuButton * QuitBtn;

};

#endif // MENU_H

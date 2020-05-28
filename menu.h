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

    QList<MenuButton *> getButtonList() const;

private:
    QList<MenuButton *> buttonList;

};

#endif // MENU_H

#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "player.h"
#include "element.h"
#include "virus.h"


class Map
{
public:
    Map();

    void readExample();

    QList<Element *> getElementList() const;
    QList<Unit *> getUnitList() const;
    Player *getPlayer() const;
    QImage getBackground() const;
    int getWidth() const;
    int getHeight() const;

private:
    QImage background;
    Player * player;
    QList<Element *> elementList;
    QList<Unit *> unitList;

    int width;
    int height;
};

#endif // MAP_H

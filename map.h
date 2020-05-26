#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "player.h"
#include "element.h"
#include "virus.h"
#include "heart.h"
#include "mask.h"
#include "gel.h"



class Map
{
public:
    Map();

    void readExample();

    QList<Element *> getElementList() const;
    QList<Unit *> getUnitList() const;
    QList<consoObject *> getConsoObjectList() const;
    Player *getPlayer() const;
    QImage getBackground() const;
    int getWidth() const;
    int getHeight() const;

private:
    QImage background;
    Player * player;
    QList<Element *> elementList;
    QList<Unit *> unitList;
    QList<consoObject *> consoObjectList;

    int width;
    int height;
};

#endif // MAP_H

#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "playerview.h"


class Map : public QObject,public QGraphicsPixmapItem
{
public:
    Map();

private:
    QGraphicsScene * scene;
    PlayerView * player;
};

#endif // MAP_H

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "unit.h"

class Player : public Unit{

public:
    Player();
    void Jump();

};

#endif // PLAYER_H

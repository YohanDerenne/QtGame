#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

#include "unit.h"
#include "wall.h"
#include "configuration.h"
#include "info.h"


class Player : public Unit{

public:
    Player();
    void jump();
    void bounce();
    void setLife(int value);

    Info *getInfo() const;
    void setInfo(Info *value);

private:
    Info * info;
};

#endif // PLAYER_H

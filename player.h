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
#include "mask.h"


class Player : public Unit{
    Q_OBJECT
public:
    Player();
    void jump();
    void bounce();
    void setLife(int value);

    Info *getInfo() const;
    void setInfo(Info *value);

    void putMask();

public slots:
    void takeOffMask();

private:
    Info * info;
    QTimer * maskTimer;
};

#endif // PLAYER_H

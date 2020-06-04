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
#include "gelprojectile.h"

/**
 * \file player.h
 * \brief Player class, inherits the "Unit" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
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
    void catchGel();

    bool getGotGel() const;

    GelProjectile * launchGel(int xOffset,int yOffset);

    bool getFire() const;
    void setFire(bool value);

    QTimer *getMaskTimer() const;

    QTimer *getGelTimer() const;

    bool getGotMask() const;

public slots:
    void takeOffMask();
    void disableGel();

private:
    Info * info;
    QTimer * maskTimer;
    QTimer * gelTimer;
    bool gotGel;
    bool gotMask;
    bool fire;
};

#endif // PLAYER_H

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

    /**
     * \fn Player()
     * \brief Constructor of the Player class
     * initializes attributes of the Player
     */
    Player();


    /**
     * \fn jump()
     * \brief the player jumps
     */
    void jump();

    /**
     * \fn jump()
     * \brief the player bounces
     */
    void bounce();

    /**
     * \fn setLife(int value);
     * \brief changes the player's life
     * \param value, value to be assigned to the player's life
     */
    void setLife(int value);



    /**
     * \fn  Info * getInfo() const;
     * \brief accessors for the "info" attribute.
     * \return a Info * , value of info
     *
     */
    Info *getInfo() const;


    /**
     * \fn  void setInfo(Info *value);
     * \brief Modification accessors for the "info" attribute.
     * \param value, value to assign to info
     *
     */
    void setInfo(Info *value);

    /**
     * \fn  void putMask();
     * \brief equips the player with a mask
     *
     */
    void putMask();

    /**
     * \fn  void catchGel();
     * \brief equips the player with a gel
     *
     */
    void catchGel();

    /**
     * \fn  void catchGel();
     * \brief return true if player has a gel
     * \return true if player has a gel
     *
     */
    bool getGotGel() const;

    /**
     * \fn  GelProjectile * launchGel(int xOffset,int yOffset);
     * \brief launches a "gel" type projectile
     * \return a GelProjectile*, the object that will be the projectile
     *
     */
    GelProjectile * launchGel(int xOffset,int yOffset);

    /**
     * \fn  void getFire();
     * \brief accessors of the attribute "fire"
     * \return value of the attribute "fire"
     *
     */
    bool getFire() const;

    /**
     * \fn  void setFire(bool value);
     * \brief Modification accessors for the "fire" attribute.
     * \param value, value to assign to fire
     *
     */
    void setFire(bool value);

    /**
     * \fn QTimer *getMaskTimer() const;
     * \brief accessors of the attribute "maskTimer"
     * \return value of the attribute "maskTimer"
     *
     */
    QTimer *getMaskTimer() const;

    /**
     * \fn QTimer *getGelTimer() const;
     * \brief accessors of the attribute "gelTimer"
     * \return value of the attribute "gelTimer"
     *
     */
    QTimer *getGelTimer() const;

    /**
     * \fn  void getGotMask();
     * \brief accessors of the attribute "gotMask"
     * \return value of the attribute "gotMask"
     *
     */
    bool getGotMask() const;

public slots:

    /**
     * \fn  void getGotMask();
     * \brief take the mask off the player
     *
     */
    void takeOffMask();

    /**
     * \fn  void getGotMask();
     * \brief take the gel off the player
     *
     */
    void disableGel();

private:
    /**
     * \var Info * info;
     * \brief An Info Object, containing the player's information
     *
     */
    Info * info;

    /**
     * \var QTimer * maskTimer;
     * \brief The timer of the time the mask is worn
     *
     */
    QTimer * maskTimer;

    /**
     * \var QTimer * gelTimer;
     * \brief The timer of the time the gel is worn
     *
     */
    QTimer * gelTimer;

    /**
     * \var bool gotGel;
     * \brief if the player has a gel
     *
     */
    bool gotGel;

    /**
     * \var bool gotMask;
     * \brief if the player has a mask
     *
     */
    bool gotMask;

    /**
     * \var bool fire;
     * \brief if the player has a fire
     *
     */
    bool fire;
};

#endif // PLAYER_H

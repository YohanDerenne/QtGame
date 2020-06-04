#ifndef INFO_H
#define INFO_H

#include <QGraphicsItemGroup>
#include "configuration.h"
#include "lifebar.h"

/**
 * \file info.h
 * \brief player information Class
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Info : public QGraphicsItemGroup
{
public:
    /**
     * \fn Info()
     * \brief Constructor of the Info class
     * initializes player information
     */
    Info();
    /**
     * \fn ~Info()
     * \brief destructor of the Info class
     * removes all objects from the player's information
     */
    ~Info();

    /**
     * \fn  void setNbLife(int value)
     * \brief player's life attribute modification accessors.
     * \param value, value to assign to the player's life number
     *
     */
    void setNbLife(int value);

    /**
     * \fn  void setNbLife(int value)
     * \brief maskIndicator life attribute modification accessors.
     * \param state, true if the player has a mask
     *
     */
    void setMaskIndicator(bool state);

    /**
     * \fn  void setNbLife(int value)
     * \brief gelIndicator attribute modification accessors.
     * \param state, true if the player has a gel
     *
     */
    void setGelIndicator(bool state);

private:
    LifeBar * life;
    Element * maskIndicator;
    Element * gelIndicator;
    void updateIndicatorPos();
};

#endif // INFO_H

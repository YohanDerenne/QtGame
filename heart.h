#ifndef HEART_H
#define HEART_H
#include "consoObject.h"
#include "configuration.h"


/**
 * \file heart.h
 * \brief Heart consumable class, inherits the "consoObject" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Heart: public consoObject
{
public:
    /**
     * \fn Heart()
     * \brief Constructor of the Heart class
     * Reset the type to "Heart" the width and height of the heart with the parameters in the class Configuration.h
     */
    Heart();


    /**
     * \fn void applyEffect(Unit * unit);
     * \brief Application of the Heart consumable
     * \param unit, the object Unit that asks to consume the heart
     * Verifies if the Unit object is a "player" if yes it affects the consumable "Heart".
     */
    void applyEffect(Unit * unit);
};

#endif // HEART_H

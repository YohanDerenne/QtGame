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
    Heart();
    void applyEffect(Unit * unit);
};

#endif // HEART_H

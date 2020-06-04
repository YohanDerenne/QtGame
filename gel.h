#ifndef GEL_H
#define GEL_H
#include "consoObject.h"
#include "configuration.h"
#include "player.h"

/**
 * \file gel.h
 * \brief Class of the consumable of type Gel, inherits the class "consoObject".
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Gel : public consoObject
{
public:
    Gel();
    void applyEffect(Unit * unit);
};

#endif // GEL_H

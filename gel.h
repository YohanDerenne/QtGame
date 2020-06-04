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
    /**
     * \fn Gel()
     * \brief Constructor of the Gel class
     * Reset the type to "gel" the width and height of the gel with the parameters in the class Configuration.h
     */
    Gel();

    /**
     * \fn void applyEffect(Unit * unit);
     * \brief Application of the gel consumable
     * \param unit, the object Unit that asks to consume the gel
     * Verifies if the Unit object is a "player" if yes it affects the consumable "gel".
     */
    void applyEffect(Unit * unit);
};

#endif // GEL_H

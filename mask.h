#ifndef MASK_H
#define MASK_H
#include "consoObject.h"
#include "configuration.h"

/**
 * \file mask.h
 * \brief Class of the Mask type consumable, inherits from the "consoObject" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Mask: public consoObject
{
public:

    /**
     * \fn Mask()
     * \brief Constructor of the Mask class
     * Reset the type to "Mask" the width and height of the heart with the parameters in the class Configuration.h
     */
    Mask();
    /**
     * \fn void applyEffect(Unit * unit);
     * \brief Application of the Mask consumable
     * \param unit, the object Unit that asks to consume the Mask
     * Verifies if the Unit object is a "player" if yes it affects the consumable "Mask".
     */
    void applyEffect(Unit * unit);

private:
    QTimer * bonusTimer;
};

#endif // MASK_H

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
    Mask();
    void applyEffect(Unit * unit);

private:
    QTimer * bonusTimer;
};

#endif // MASK_H

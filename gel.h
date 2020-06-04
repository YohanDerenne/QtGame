#ifndef GEL_H
#define GEL_H
#include "consoObject.h"
#include "configuration.h"
#include "player.h"

/**
 * \file gel.h
 * \brief Classe du consommable de type Gel, hérite de la classe "consoObject".
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

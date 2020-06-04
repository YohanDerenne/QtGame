#ifndef HEART_H
#define HEART_H
#include "consoObject.h"
#include "configuration.h"


/**
 * \file heart.h
 * \brief Classe du consommable de type coeur, hérite de la classe "consoObject".
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

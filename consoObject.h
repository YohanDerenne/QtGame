#ifndef CONSOOBJECT_H
#define CONSOOBJECT_H

#include "configuration.h"
#include "element.h"
#include "unit.h"

/**
 * \file consoObject.h
 * \brief Classe des elements consommables par le joueur, hérite de la classe "Element".
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class consoObject : public Element
{
public:

    consoObject();
    int getDurationOfEffect() const;
    void setDurationOfEffect(int value);
    virtual void applyEffect(Unit * unit)=0;

/*protected :
    virtual void applyEffect(Unit unit) = 0;*/

private:
    int durationOfEffect;
};

#endif // CONSOOBJECT_H

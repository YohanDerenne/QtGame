#ifndef CONSOOBJECT_H
#define CONSOOBJECT_H

#include "configuration.h"
#include "element.h"
#include "unit.h"

/**
 * \file consoObject.h
 * \brief Class of elements consumable by the player, inherited from the "Element" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class consoObject : public Element
{
public:


    /**
     * \fn consoObject();
     * \brief Consrtructor of the consoObject class
     *
     * Reset the durationOfEffect attribute to 0
     */
    consoObject();

    /**
     * \fn int getDurationOfEffect() const
     * \brief Accessor to the "durationOfEffect" attribute.
     * \return The value of the durationOfEffect attribute of the "consoObject" object.
     */
    int getDurationOfEffect() const;
    /**
     * \fn  void setDurationOfEffect(int value)
     * \brief durationOfEffect attribute modification accessors.
     * \param value, value to assign to the durationOfEffect attribute
     *
     */
    void setDurationOfEffect(int value);

    virtual void applyEffect(Unit * unit)=0;

private:
    int durationOfEffect;
};

#endif // CONSOOBJECT_H

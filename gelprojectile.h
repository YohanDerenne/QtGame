#ifndef GELPROJECTILE_H
#define GELPROJECTILE_H

#include "projectile.h"

/**
 * \file gelprojectile.h
 * \brief Class of projectile Gel, inherits the class "Projectile".
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class GelProjectile : public Projectile
{
public:
    /**
     * \fn GelProjectile(bool right);
     * \brief Constructor of the GelProjectile class
     * Initializes the isRightSide attribute with the value in parameter and the other default attributes
     */
    GelProjectile(bool right);

    /**
     * \fn void touch(Unit *);
     * \brief Inflicts 1 damage to the element that is hit by the projectile.
     */
    void touch(Unit *);
};

#endif // GELPROJECTILE_H

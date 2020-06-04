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
    GelProjectile(bool right);
    void touch(Unit *);
};

#endif // GELPROJECTILE_H

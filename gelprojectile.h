#ifndef GELPROJECTILE_H
#define GELPROJECTILE_H

#include "projectile.h"

/**
 * \file gelprojectile.h
 * \brief Classe du projectile Gel, hérite de la classe "Projectile".
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

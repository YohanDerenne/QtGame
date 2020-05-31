#ifndef GELPROJECTILE_H
#define GELPROJECTILE_H

#include "projectile.h"

class GelProjectile : public Projectile
{
public:
    GelProjectile(bool right);
    void touch(Unit *);
};

#endif // GELPROJECTILE_H

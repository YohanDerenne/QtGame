#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "unit.h"

/**
 * \file projectfile.h
 * \brief Projectile class, inherits the "Unit" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Projectile : public Unit
{
public:
    Projectile();
    virtual void touch(Unit *)=0;
    void move();
    bool isMaxDist();

    void setBegin(int value);

private:
    int maxDist;
    int begin;
};

#endif // PROJECTILE_H

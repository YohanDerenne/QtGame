#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "unit.h"

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

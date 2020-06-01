#include "projectile.h"
#include <QDebug>

Projectile::Projectile() : Unit()
{
    maxDist = 1000;
}

void Projectile::move()
{
    setPos(x()+xForce,y());
}

void Projectile::setBegin(int value)
{
    begin = value;
}


bool Projectile::isMaxDist()
{
    if(isRightSide){
        if( x() - begin < maxDist){
            return false;
        }
        else{
            return true;
        }
    }
    else{
        if(begin - x() < maxDist){
            return false;
        }
        else{
            return true;
        }
    }
}


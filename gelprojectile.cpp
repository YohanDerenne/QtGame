#include "gelprojectile.h"

GelProjectile::GelProjectile(bool right) : Projectile()
{
    isRightSide = right;
    height = PROJ_HEIGHT;
    width = PROJ_WIDTH;
    setSprite(":/ressources/images/projectile.png");

    // inital force
    if(isRightSide){
        xForce = 13;
    }
    else{
        xForce = -13;
    }


}

void GelProjectile::touch(Unit * unit)
{
    unit->receiveDammage(1);
}

#include "heart.h"

Heart::Heart()
{
    type = "heart";
    width = LIFE_WIDTH;
    height = LIFE_HEIGHT;

    setSprite(":/ressources/images/heart.png");

}

void Heart::applyEffect(Unit *unit)
{
    unit->setLife(unit->getLife() + 1);
}

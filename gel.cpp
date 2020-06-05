#include "gel.h"

Gel::Gel()
{
    type = "gel";
    width = GEL_WIDTH;
    height = GEL_HEIGHT;

    // set graphic
    setSprite(":/ressources/images/gel.png");

}

void Gel::applyEffect(Unit *unit)
{
    if(unit->getType() == "player"){
        Player * player = static_cast<Player*>(unit);
        player->catchGel();
    }
}

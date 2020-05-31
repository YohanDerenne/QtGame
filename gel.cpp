#include "gel.h"

Gel::Gel()
{
    type = "gel";
    width = GEL_WIDTH;
    height = GEL_HEIGHT;

    // set graphic
    QPixmap img = QPixmap(":/ressources/images/gel.png");
    img = img.scaled(width,height);
    setPixmap(img);

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}

void Gel::applyEffect(Unit *unit)
{
    if(unit->getType() == "player"){
        Player * player = static_cast<Player*>(unit);
        player->catchGel();
    }
}

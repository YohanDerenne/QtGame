#include "mask.h"
#include "player.h"

#include <QColor>

Mask::Mask()
{
    type = "mask";
    width = MASK_WIDTH;
    height = MASK_HEIGHT;

    // set graphic
    QPixmap img = QPixmap(":/ressources/images/mask.png");
    img = img.scaled(width,height);
    setPixmap(img);

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}

void Mask::applyEffect(Unit *unit)
{
    if(unit->getType() == "player"){
        Player * player = static_cast<Player*>(unit);
        player->putMask();
    }
}

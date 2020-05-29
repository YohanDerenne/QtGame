#include "mask.h"

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

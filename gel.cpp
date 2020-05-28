#include "gel.h"

Gel::Gel()
{
    width = GEL_WIDTH;
    height = GEL_HEIGHT;

    // set graphic
    QPixmap img = QPixmap(":/ressources/images/gel.jpg");
    img = img.scaled(width,height);
    setPixmap(img);

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}

#include "heart.h"

Heart::Heart()
{
    width = LIFE_WIDTH;
    height = LIFE_HEIGHT;

    // set graphic
    QPixmap img = QPixmap(":/ressources/images/life.png");
    img = img.scaled(width,height);
    setPixmap(img);

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

}

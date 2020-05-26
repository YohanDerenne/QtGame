#include "virus.h"


Virus::Virus() : Unit()
{
    width = VIRUS_WIDTH;
    height = VIRUS_HEIGHT;

    // set graphic
    QPixmap img = QPixmap(":/ressources/images/virus.png");
    img = img.scaled(width,height);
    setPixmap(img);

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    type = "virus";
}

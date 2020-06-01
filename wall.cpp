#include "wall.h"


Wall::Wall() : FixedBlock()
{
    QPixmap blocSprite = QPixmap(":/ressources/images/bloc.png");
    blocSprite = blocSprite.scaled(BLOC_SIZE,BLOC_SIZE);
    setPixmap(blocSprite);

    width = BLOC_SIZE;
    height = BLOC_SIZE;

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    type = "wall";

}

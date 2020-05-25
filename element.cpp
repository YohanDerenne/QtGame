#include "element.h"

Element::Element()
{
    height = 0;
    width = 0;
}

int Element::getWidth() const
{
    return width;
}

void Element::setWidth(int value)
{
    width = value;
}

int Element::getHeight() const
{
    return height;
}

void Element::setHeight(int value)
{
    height = value;
}

void Element::setSprite(QString ressource)
{
    // set graphic
    QPixmap img = QPixmap(ressource);
    img = img.scaled(width,height);
    // If in the right side
    if(!isRightSide){
        img = img.transformed(QTransform().scale(-1, 1));
    }
    setPixmap(img);

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

}

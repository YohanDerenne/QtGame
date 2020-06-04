#include "element.h"

Element::Element()
{
    height = 0;
    width = 0;
}

Element::Element(int height, int width)
{
    this->height = height;
    this->width = width;
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

}

QString Element::getType() const
{
    return type;
}

void Element::setType(const QString &value)
{
    type = value;
}

int Element::getSpawnX() const
{
    return spawnX;
}

void Element::setSpawnX(int value)
{
    spawnX = value;
}

int Element::getSpawnY() const
{
    return spawnY;
}

void Element::setSpawnY(int value)
{
    spawnY = value;
}

void Element::respawn()
{
    setPos(spawnX,spawnY);
}

int Element::getIsRightSide() const
{
    return isRightSide;
}

void Element::setIsRightSide(int value)
{
    isRightSide = value;
}

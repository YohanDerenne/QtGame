#include "info.h"
#include <QBrush>
#include <QFont>
#include <QColor>

Info::Info()
{
    // Life info
    life = new LifeInfo();
    life->setX(10);
    life->setY(5);

    // Nb Life info
    QGraphicsTextItem * lives = new QGraphicsTextItem("4");
    lives->setPos(25,15);
    QFont lifeFont;
    //lives->setDefaultTextColor(Qt::white);
    lifeFont.setBold(true);
    lifeFont.setPixelSize(20);
    lives->setFont(lifeFont);

    // Background Info
    zone = new QGraphicsRectItem(0,0,WINDOW_WIDTH + 10,60);
    zone->setBrush(Qt::black);

    // Add all item to the group
    // this->addToGroup(zone);
    this->addToGroup(life);
    this->addToGroup(lives);
}

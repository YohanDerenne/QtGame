#include "info.h"

Info::Info()
{
    int separator = 10;

    life = new LifeBar();
    this->addToGroup(life);

    maskIndicator = new Element(50,70);
    maskIndicator->setSprite(":/ressources/images/mask.png");
    maskIndicator->setPos(0,separator + life->getHeartHeight());
    maskIndicator->hide();
    this->addToGroup(maskIndicator);
    setPos(10,10);
}

Info::~Info()
{
    delete life;
    delete maskIndicator;
}

void Info::setNbLife(int value)
{
    life->setNbHeart(value,x(),y());
}

void Info::setMaskIndicator(bool state)
{
    if(state)
        maskIndicator->show();
    else
        maskIndicator->hide();
}

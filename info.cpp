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

    gelIndicator = new Element(50,30);
    gelIndicator->setSprite(":/ressources/images/gel.png");
    gelIndicator->setPos(maskIndicator->getWidth() + separator,separator + life->getHeartHeight());
    gelIndicator->hide();
    this->addToGroup(gelIndicator);
    setPos(10,10);
}

Info::~Info()
{
    delete life;
    delete maskIndicator;
    delete gelIndicator;
}

void Info::setNbLife(int value)
{
    life->setNbHeart(value,x(),y());
}

void Info::setMaskIndicator(bool state)
{
    if(state){
        maskIndicator->show();
        maskIndicator->setType("shown");
    }

    else{
        maskIndicator->hide();
        maskIndicator->setType("hide");
    }
    updateIndicatorPos();
}

void Info::setGelIndicator(bool state)
{
    if(state){
        gelIndicator->show();
        gelIndicator->setType("shown");

    }

    else{
        gelIndicator->hide();
        gelIndicator->setType("hide");
    }
    updateIndicatorPos();
}

void Info::updateIndicatorPos()
{
    int xUsed = 0;
    int separator = 10;
    if(gelIndicator->getType() == "shown"){
        gelIndicator->setPos(xUsed + separator,separator + life->getHeartHeight());
        xUsed = gelIndicator->getWidth();
    }
    if(maskIndicator->getType() == "shown"){
        maskIndicator->setPos(xUsed + separator,separator + life->getHeartHeight());
        xUsed = maskIndicator->getWidth();
    }
}

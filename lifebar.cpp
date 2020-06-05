#include "lifebar.h"

LifeBar::LifeBar()
{
    heartWidth = 50;
    heartHeight = 50;
    HeartList = new QList<Element *>();
}

LifeBar::~LifeBar()
{
    clearHearts();
    delete HeartList;
}

void LifeBar::setNbHeart(int nb,int x,int y)
{
    clearHearts();
    int heartGap = 10;
    for(int index = 0 ; index < nb ; index ++){
        Element * heart = new Element();
        heart->setHeight(heartHeight);
        heart->setWidth(heartHeight);
        heart->setSprite(":ressources/images/heart.png");
        heart->setPos(index * (heartWidth + heartGap) + x, y);
        this->addToGroup(heart);
        HeartList->append(heart);
    }
}

void LifeBar::clearHearts()
{
    foreach(Element * heart,*HeartList){
        this->removeFromGroup(heart);
        delete heart;
    }
    HeartList->clear();
}

int LifeBar::getHeartWidth() const
{
    return heartWidth;
}

int LifeBar::getHeartHeight() const
{
    return heartHeight;
}

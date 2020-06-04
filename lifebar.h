#ifndef LIFEBAR_H
#define LIFEBAR_H

#include <QGraphicsItemGroup>
#include "element.h"
#include <QDebug>

/**
 * \file lifebar.h
 * \brief Classe de la barre de vie.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class LifeBar : public QGraphicsItemGroup
{
public:
    LifeBar();
    ~LifeBar();
    void setNbHeart(int nb,int x, int y);
    void clearHearts();

    int getHeartWidth() const;
    int getHeartHeight() const;

private:
    QList<Element *> * HeartList;
    int heartWidth;
    int heartHeight;
};

#endif // LIFEBAR_H

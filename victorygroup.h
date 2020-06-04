#ifndef VICTORYGROUP_H
#define VICTORYGROUP_H

#include <QGraphicsItemGroup>
#include "menubutton.h"
#include "configuration.h"
#include <QGraphicsTextItem>

/**
 * \file victoryGroup.h
 * \brief Classe pour gérer la victoire de la partie
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class VictoryGroup : public QGraphicsItemGroup
{
public:
    VictoryGroup();
    ~VictoryGroup();

    MenuButton *getRetryBtn() const;
    MenuButton *getBackMenuBtn() const;

private:
    MenuButton * retryBtn;
    MenuButton * backMenuBtn;
    QGraphicsTextItem * title;
};

#endif // VICTORYGROUP_H

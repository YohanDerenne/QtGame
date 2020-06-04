#ifndef VICTORYGROUP_H
#define VICTORYGROUP_H

#include <QGraphicsItemGroup>
#include "menubutton.h"
#include "configuration.h"
#include <QGraphicsTextItem>

/**
 * \file victoryGroup.h
 * \brief Class to manage the victory of the game
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

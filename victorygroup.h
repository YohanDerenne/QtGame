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
    /**
     * \fn VictoryGroup()
     * \brief Constructor of the VictoryGroup class
     * the objects that form the victory flag
     */
    VictoryGroup();
    /**
     * \fn ~VictoryGroup()
     * \brief destructor of the VictoryGroup class
     * removes all objects that form the victory flag
     */
    ~VictoryGroup();

    /**
     * \fn  MenuButton *getRetryBtn() const;
     * \brief accessors for the "retryBtn" attribute.
     * \return a MenuButton object, value of attribute retryBtn
     *
     */
    MenuButton *getRetryBtn() const;
    /**
     * \fn  MenuButton *getBackMenuBtn() const;
     * \brief accessors for the "backMenuBtn" attribute.
     * \return a MenuButton object, value of attribute backMenuBtn
     *
     */
    MenuButton *getBackMenuBtn() const;

private:

    /**
     * \var  MenuButton * retryBtn;
     * \brief button to play the level again
     *
     */
    MenuButton * retryBtn;

    /**
     * \var  MenuButton * backMenuBtn;
     * \brief button to return to the main menu
     *
     */
    MenuButton * backMenuBtn;

    /**
     * \var QGraphicsTextItem * title;
     * \brief Name of Victory
     *
     */
    QGraphicsTextItem * title;
};

#endif // VICTORYGROUP_H

#ifndef LIFEBAR_H
#define LIFEBAR_H

#include <QGraphicsItemGroup>
#include "element.h"
#include <QDebug>

/**
 * \file lifebar.h
 * \brief Life bar class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class LifeBar : public QGraphicsItemGroup
{
public:

    /**
     * \fn LifeBar()
     * \brief Constructor of the LifeBar class
     * initializes player's lifebar information
     */
    LifeBar();
    /**
     * \fn ~LifeBar()
     * \brief destructor of the LifeBar class
     * removes all objects from the player's lifebar
     */
    ~LifeBar();

    /**
     * \fn void setNbHeart(int nb,int x, int y);
     * \brief affects life at the lifebar
     * \param nb, the number of hearts assigned to the life bar
     * \param x, the "x" position of the heart we create
     * \param y, the "y" position of the heart we create
     * \brief destructor of the LifeBar class
     */
    void setNbHeart(int nb,int x, int y);

    /**
     * \fn void clearHearts()
     * \brief destructor of the LifeBar class
     * removes all objects from the player's lifebar
     */
    void clearHearts();

    /**
     * \fn int getHeartWidth() const
     * \brief Accessor of the "heartWidth" attribute.
     * \return The value of the heartWidth attribute of the "LifeBar" object.
     */
    int getHeartWidth() const;
    /**
     * \fn int getHeartHeight() const
     * \brief Accessor of the "heartHeight" attribute.
     * \return The value of the heartHeight attribute of the "LifeBar" object.
     */
    int getHeartHeight() const;

private:


    /**
     * \var  QList<Element *> HeartList;
     * \brief The list of hearts owned by the lifebar
     *
     */
    QList<Element *> * HeartList;

    /**
     * \var int heartWidth;
     * \brief the width of a heart
     *
     */
    int heartWidth;

    /**
     * \var int heartHeight;
     * \brief the height of a heart
     *
     */
    int heartHeight;
};

#endif // LIFEBAR_H

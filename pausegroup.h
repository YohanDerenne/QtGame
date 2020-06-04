#ifndef PAUSEGROUP_H
#define PAUSEGROUP_H

#include <QGraphicsItemGroup>
#include "menubutton.h"
#include "configuration.h"

/**
 * \file pausegroup.h
 * \brief Pause menu class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class PauseGroup : public QGraphicsItemGroup
{
public:

    /**
     * \fn PauseGroup()
     * \brief Constructor of the PauseGroup class
     * Initiates pause mode
     */
    PauseGroup();
    /**
     * \fn ~PauseGroup()
     * \brief destructor of the PauseGroup class
     * removes all objects from the pause mode
     */
    ~PauseGroup();


    /**
     * \fn int *getContinueBtn() const
     * \brief Accessor of the "continueBtn" attribute.
     * \return The value of the continueBtn attribute of the "PauseGroup" object.
     */
    MenuButton *getContinueBtn() const;


    /**
     * \fn int *getBackMenuBtn() const
     * \brief Accessor of the "backMenuBtn" attribute.
     * \return The value of the backMenuBtn attribute of the "PauseGroup" object.
     */
    MenuButton *getBackMenuBtn() const;

private:
    MenuButton * continueBtn;
    MenuButton * backMenuBtn;
    QGraphicsTextItem * title;
};

#endif // PAUSEGROUP_H

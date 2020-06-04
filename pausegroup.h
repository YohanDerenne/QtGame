#ifndef PAUSEGROUP_H
#define PAUSEGROUP_H

#include <QGraphicsItemGroup>
#include "menubutton.h"
#include "configuration.h"

/**
 * \file pausegroup.h
 * \brief Classe du menu de pause.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class PauseGroup : public QGraphicsItemGroup
{
public:
    PauseGroup();
    ~PauseGroup();
    MenuButton *getContinueBtn() const;

    MenuButton *getBackMenuBtn() const;

private:
    MenuButton * continueBtn;
    MenuButton * backMenuBtn;
    QGraphicsTextItem * title;
};

#endif // PAUSEGROUP_H

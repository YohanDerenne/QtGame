#ifndef PAUSEGROUP_H
#define PAUSEGROUP_H

#include <QGraphicsItemGroup>
#include "menubutton.h"
#include "configuration.h"

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
};

#endif // PAUSEGROUP_H

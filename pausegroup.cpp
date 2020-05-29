#include "pausegroup.h"

PauseGroup::PauseGroup()
{
    continueBtn = new MenuButton("Continue");
    backMenuBtn = new MenuButton("Menu");

    int yOffset = 100;
    continueBtn->move(WINDOW_WIDTH / 2 - continueBtn->width() / 2,yOffset);
    backMenuBtn->move(WINDOW_WIDTH / 2 - backMenuBtn->width() / 2,continueBtn->height() + BTN_GAP + yOffset);;
}

PauseGroup::~PauseGroup()
{
    delete continueBtn;
    delete backMenuBtn;
}

MenuButton *PauseGroup::getContinueBtn() const
{
    return continueBtn;
}

MenuButton *PauseGroup::getBackMenuBtn() const
{
    return backMenuBtn;
}

#include "pausegroup.h"

PauseGroup::PauseGroup()
{
    continueBtn = new MenuButton("Continue");
    backMenuBtn = new MenuButton("Menu");

    int yOffset = 120;
    int borderOffset = 50;

    // rectangl
    QGraphicsRectItem * rect = new QGraphicsRectItem(0,0,continueBtn->width() + borderOffset, yOffset * 3 + borderOffset);
    rect->setBrush(Qt::white);
    rect->setPos(WINDOW_WIDTH / 2 - continueBtn->width() / 2 - borderOffset/2 ,yOffset - borderOffset/2);
    this->addToGroup(rect);

    // menu title
    title = new QGraphicsTextItem("Pause");
    QFont font = QFont("Agency FB",60);
    font.setBold(true);
    title->setFont(font);
    title->setPos(WINDOW_WIDTH / 2 - 170 / 2,yOffset);
    addToGroup(title);

    // Set button in the midle of the screen
    continueBtn->move(WINDOW_WIDTH / 2 - continueBtn->width() / 2,yOffset * 2);
    backMenuBtn->move(WINDOW_WIDTH / 2 - backMenuBtn->width() / 2, yOffset * 3);


}

PauseGroup::~PauseGroup()
{
    delete continueBtn;
    delete backMenuBtn;
    delete title;
}

MenuButton *PauseGroup::getContinueBtn() const
{
    return continueBtn;
}

MenuButton *PauseGroup::getBackMenuBtn() const
{
    return backMenuBtn;
}

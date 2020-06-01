#include "victorygroup.h"

VictoryGroup::VictoryGroup() : QGraphicsItemGroup()
{
    retryBtn = new MenuButton("Retry");
    backMenuBtn = new MenuButton("Menu");

    int yOffset = 120;
    int borderOffset = 50;

    // rectangl
    QGraphicsRectItem * rect = new QGraphicsRectItem(0,0,backMenuBtn->width() + borderOffset, yOffset * 3 + borderOffset);
    rect->setBrush(Qt::white);
    rect->setPos(WINDOW_WIDTH / 2 - backMenuBtn->width() / 2 - borderOffset/2 ,yOffset - borderOffset/2);
    this->addToGroup(rect);

    // menu title
    title = new QGraphicsTextItem("Victory !");
    QFont font = QFont("Agency FB",60);
    font.setBold(true);
    title->setFont(font);
    title->setPos(WINDOW_WIDTH / 2 - 210 / 2,yOffset);
    addToGroup(title);

    // Set button in the midle of the screen
    retryBtn->move(WINDOW_WIDTH / 2 - retryBtn->width() / 2,yOffset * 2);
    backMenuBtn->move(WINDOW_WIDTH / 2 - backMenuBtn->width() / 2, yOffset * 3);

}

VictoryGroup::~VictoryGroup()
{
    delete retryBtn;
    delete backMenuBtn;
}

MenuButton *VictoryGroup::getRetryBtn() const
{
    return retryBtn;
}

MenuButton *VictoryGroup::getBackMenuBtn() const
{
    return backMenuBtn;
}

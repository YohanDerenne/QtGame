#include "player.h"
#include "wall.h"
#include "configuration.h"
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

Player::Player() : Unit()
{
    width = PLAYER_WIDTH;
    height = PLAYER_HEIGHT;

    // set graphic
    QPixmap img = QPixmap(":/ressources/images/player.png");
    img = img.scaled(width,height);
    setPixmap(img);

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

}

void Player::Jump()
{
    if(flying == false){
        yForce = -900;
        flying = true;
        jumping = true;
    }
}





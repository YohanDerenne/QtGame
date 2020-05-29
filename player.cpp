#include "player.h"

Player::Player() : Unit()
{
    width = PLAYER_WIDTH;
    height = PLAYER_HEIGHT;

    setSprite(":/ressources/images/player/1.png");
    type = "player";
}

void Player::jump()
{
    if(flying == false){
        yForce = -900;
        updateMovementStates();
    }
}

void Player::bounce()
{
    yForce = -200;
    updateMovementStates();
}

void Player::setLife(int value)
{
    life = value;
    if(life <= 0)
        alive = false;
    else
        alive = true;
    getInfo()->setNbLife(life);
}

Info *Player::getInfo() const
{
    return info;
}

void Player::setInfo(Info *value)
{
    info = value;
}






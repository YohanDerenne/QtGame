#include "player.h"

Player::Player() : Unit()
{
    width = PLAYER_WIDTH;
    height = PLAYER_HEIGHT;

    setSprite(":/ressources/images/player/1.png");
    type = "player";
}

void Player::Jump()
{
    if(flying == false){
        yForce = -900;
        updateMovementStates();
    }
}





#include "player.h"

Player::Player() : Unit()
{
    width = PLAYER_WIDTH;
    height = PLAYER_HEIGHT;
    gotGel = false;
    fire = false;
    gotMask = false;

    setSprite(":/ressources/images/player/1.png");
    type = "player";

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    maskTimer = NULL;
    gelTimer = NULL;
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

void Player::putMask()
{
    setImmune(true);
    gotMask = true;
    maskTimer = new QTimer();
    maskTimer->start(5000);
    connect(maskTimer,&QTimer::timeout,this,&Player::takeOffMask);
    info->setMaskIndicator(true);
}

void Player::catchGel()
{
    gotGel = true;
    gelTimer = new QTimer();
    gelTimer->start(5000);
    connect(gelTimer,&QTimer::timeout,this,&Player::disableGel);
    info->setGelIndicator(true);
}

void Player::takeOffMask()
{
    gotMask = false;
    delete maskTimer;
    maskTimer = NULL;
    setImmune(false);
    info->setMaskIndicator(false);
}

void Player::disableGel()
{
    delete gelTimer;
    gelTimer = NULL;
    gotGel = false;
    info->setGelIndicator(false);
}

bool Player::getGotMask() const
{
    return gotMask;
}

QTimer *Player::getGelTimer() const
{
    return gelTimer;
}

QTimer *Player::getMaskTimer() const
{
    return maskTimer;
}

bool Player::getFire() const
{
    return fire;
}

void Player::setFire(bool value)
{
    fire = value;
}

bool Player::getGotGel() const
{
    return gotGel;
}

GelProjectile *Player::launchGel(int xPlanOffset, int yPlanOffset)
{


    // create projectile
    if(getGotGel()){
        fire = true;
        GelProjectile * proj = new GelProjectile(getIsRightSide());
        if(getIsRightSide()){
            proj->setX(x() + getWidth() + xPlanOffset);
            proj->setBegin(x() + getWidth() + xPlanOffset);
        }
        else{
            proj->setX(x() + xPlanOffset);
            proj->setBegin(x() + xPlanOffset);
        }

        proj->setY(y() + getHeight() / 2 - proj->getHeight() / 2 + yPlanOffset);
        return proj;
    }
    return NULL;
}








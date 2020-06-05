#include "unit.h"

Unit::Unit() : Element()
{
    // init Physics
    flying = false;
    movingLeft = false;
    movingRight = false;
    falling = false;
    jumping = false;
    xForce = 0;
    weight = 200;
    yForce = 0;
    xAcceleration = 0.5;

    maxSpeed = MAX_SPEED;
    isRightSide = true;

    setLife(1);
    immune = false;

    immuneTimer = NULL;
}

void Unit::SetMovingRight(bool state)
{
    movingRight = state;
    if(state == true)
        isRightSide = true;
}

void Unit::SetMovingLeft(bool state)
{
    movingLeft = state;
    if(state == true)
        isRightSide = false;
}

void Unit::updateMovementStates()
{
    if(yForce > 0 )
        falling = true;
    else
        falling = false;

    if(yForce < 0){
        jumping = true;
    }
    else{
        jumping = false;
    }
    if(yForce == 0){
        flying = false;
        // better grip on the floor
        xAcceleration = 1;
    }
    else{
        flying = true;
        // lower grip in the air
        xAcceleration = 0.5;
    }
    if(xForce < 1 &&  xForce > -1 && yForce < 1 &&  yForce > -1)
        fixed = true;
    else
        fixed = false;
}

void Unit::increaseLeftForce()
{
    if(xForce > - maxSpeed){
        xForce -= 1 * xAcceleration;
    }
}

void Unit::increaseRightForce()
{
    if(xForce < maxSpeed){
        xForce += 1 * xAcceleration;
    }
}

void Unit::decreaseXForce()
{
    if(xForce > 0)
        xForce -= 1 * xAcceleration;
    if(xForce < 0)
        xForce += 1 * xAcceleration;
}

bool Unit::getFixed() const
{
    return fixed;
}

void Unit::receiveDammage(int dammage)
{
    if(!immune){
        setLife(life - dammage);
        if(type == "player"){
            immuneTimer = new QTimer();
            immuneTimer->start(1000);
            connect(immuneTimer,SIGNAL(timeout()),this,SLOT(disableImmune()));
        }
        immune = true;
    }
}

void Unit::attack(Unit *target)
{
    target->receiveDammage(1);
}

int Unit::getLife() const
{
    return life;
}

void Unit::setLife(int value)
{
    life = value;
    if(life <= 0)
        alive = false;
    else
        alive = true;
}

bool Unit::getImmune() const
{
    return immune;
}

void Unit::disableImmune()
{
    immune = false;
    delete immuneTimer;
    immuneTimer = NULL;
}

QTimer *Unit::getImmuneTimer() const
{
    return immuneTimer;
}

void Unit::setImmune(bool value)
{
    immune = value;
}

bool Unit::isAlive() const
{
    return alive;
}

float Unit::getXForce() const
{
    return xForce;
}

void Unit::setXForce(float value)
{
    xForce = value;
}

float Unit::getYForce() const
{
    return yForce;
}

void Unit::setYForce(float value)
{
    yForce = value;
    updateMovementStates();
}


bool Unit::isMovingRight() const
{
    return movingRight;
}


bool Unit::isMovingLeft() const
{
    return movingLeft;
}

int Unit::getWeight() const
{
    return weight;
}

bool Unit::isJumping() const
{
    return jumping;
}

bool Unit::isFalling() const
{
    return falling;
}

bool Unit::isFlying() const
{
    return flying;
}

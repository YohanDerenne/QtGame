#ifndef UNIT_H
#define UNIT_H

#include "element.h"

#include "configuration.h"

class Unit : public Element
{
public:
    Unit();
    void SetMovingRight(bool state);
    void SetMovingLeft(bool state);

    bool isFlying() const;
    bool isFalling() const;
    bool isJumping() const;

    int getWeight() const;

    bool isMovingLeft() const;
    void setMovingLeft(bool value);

    void setMovingRight(bool value);
    bool isMovingRight() const;

    float getYForce() const;
    void setYForce(float value);

    float getXForce() const;
    void setXForce(float value);

    void updateMovementStates();

    void increaseLeftForce();
    void increaseRightForce();
    void decreaseXForce();

    bool getFixed() const;

public slots:
    void MovePlayer();

protected :
    bool flying;
    bool falling;
    bool jumping;
    bool fixed;

    float yForce;
    float xForce;
    float xAcceleration;

    int weight;

    bool movingLeft;
    bool movingRight;

    int maxSpeed;

};

#endif // UNIT_H

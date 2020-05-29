#ifndef UNIT_H
#define UNIT_H

#include <QTimer>
#include <QObject>
#include "element.h"

#include "configuration.h"

class Unit : public QObject,public Element
{
    Q_OBJECT
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

    void receiveDammage(int dammage);
    void attack(Unit * unit);

    int getLife() const;


    bool isAlive() const;

    virtual void setLife(int value);

    bool getImmune() const;

public slots:
    //void MovePlayer();
    void disableImmune();

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

    bool alive;
    int life;
    bool immune;

    QTimer * immuneTimer;

};

#endif // UNIT_H

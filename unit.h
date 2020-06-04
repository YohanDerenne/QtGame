#ifndef UNIT_H
#define UNIT_H

#include <QTimer>
#include "element.h"

#include "configuration.h"

/**
 * \file unit.h
 * \brief Class of elements not fixed in the map, inherits from the "Element" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Unit : public Element
{
    Q_OBJECT
public:

    /**
     * \fn Unit()
     * \brief Constructor of the Unit class
     * initializes attributes of the Unit Object
     */
    Unit();

    /**
     * \fn void SetMovingRight(bool state);
     * \brief Modification accessors for the "movingRight" attribute.
     * \param state, value to be assigned to the attribute "movingRight"
     */
    void SetMovingRight(bool state);
    /**
     * \fn void SetMovingLeft(bool state);
     * \brief Modification accessors for the "movingLeft" attribute.
     * \param state, value to be assigned to the attribute "movingLeft"
     */
    void SetMovingLeft(bool state);

    /**
     * \fn bool isFlying() const;
     * \brief accessors for the "flying" attribute.
     * \return value of the attribute "flying"
     */
    bool isFlying() const;
    /**
     * \fn bool isFalling() const;
     * \brief accessors for the "falling" attribute.
     * \return value of the attribute "falling"
     */
    bool isFalling() const;
    /**
     * \fn bool isJumping() const;
     * \brief accessors for the "jumping" attribute.
     * \return value of the attribute "jumping"
     */
    bool isJumping() const;

    /**
     * \fn bool getWeight() const;
     * \brief accessors for the "weight" attribute.
     * \return value of the attribute "weight"
     */
    int getWeight() const;

    /**
     * \fn bool isMovingLeft() const;
     * \brief accessors for the "movingLeft" attribute.
     * \return value of the attribute "movingLeft"
     */
    bool isMovingLeft() const;

    /**
     * \fn void SetMovingLeft(bool state);
     * \brief Modification accessors for the "movingLeft" attribute.
     * \param state, value to be assigned to the attribute "movingLeft"
     */
    void setMovingLeft(bool value);


    /**
     * \fn void SetMovingRight(bool state);
     * \brief Modification accessors for the "movingRight" attribute.
     * \param state, value to be assigned to the attribute "movingRight"
     */
    void setMovingRight(bool value);

    /**
     * \fn bool isMovingRight() const;
     * \brief accessors for the "movingRight" attribute.
     * \return value of the attribute "movingRight"
     */
    bool isMovingRight() const;

    /**
     * \fn float getYForce() const;
     * \brief accessors for the "yForce" attribute.
     * \return value of the attribute "yForce"
     */
    float getYForce() const;
    /**
     * \fn void setYForce(float value);
     * \brief Modification accessors for the "yForce" attribute.
     * \param value, value to be assigned to the attribute "yForce"
     */
    void setYForce(float value);

    /**
     * \fn float getXForce() const;
     * \brief accessors for the "xForce" attribute.
     * \return value of the attribute "xForce"
     */
    float getXForce() const;
    /**
     * \fn void setXForce(float value);
     * \brief Modification accessors for the "xForce" attribute.
     * \param value, value to be assigned to the attribute "xForce"
     */
    void setXForce(float value);


    /**
     * \fn void updateMovementStates();
     * \brief updates all attributes of the Unit object.
     */
    void updateMovementStates();

    /**
     * \fn void increaseRightForce();
     * \brief increases the left travel speed until
     *  the maximum speed is reached
     */
    void increaseLeftForce();

    /**
     * \fn void increaseRightForce();
     * \brief increases the right travel speed until
     *  the maximum speed is reached
     */
    void increaseRightForce();

    /**
     * \fn void decreaseXForce();
     * \brief decreases the speed of the moving player until the stop.
     */
    void decreaseXForce();

    /**
     * \fn void getFixed();
     * \brief  accessors for the "fixed" attribute.
     * \return value of the attribute "fixed"
     */
    bool getFixed() const;

    /**
     * \fn void receiveDammage(int dammage);
     * \brief  affects damage received
     */
    void receiveDammage(int dammage);

    /**
     * \fn void receiveDammage(int dammage);
     * \brief  affects damage sent
     */
    void attack(Unit * unit);


    /**
     * \fn int getLife();
     * \brief  accessors for the "life" attribute.
     * \return value of the attribute "life"
     */
    int getLife() const;

    /**
     * \fn bool isAlive();
     * \brief  accessors for the "alive" attribute.
     * \return value of the attribute "alive"
     */
    bool isAlive() const;

    /**
     * \fn void setLife(int value);
     * \brief Modification accessors for the "life" attribute.
     * \param value, value to be assigned to the attribute "life"
     */
    virtual void setLife(int value);

    /**
     * \fn bool getImmune();
     * \brief  accessors for the "immune" attribute.
     * \return value of the attribute "immune"
     */
    bool getImmune() const;

    /**
     * \fn void setImmune(bool value);
     * \brief Modification accessors for the "immune" attribute.
     * \param value, value to be assigned to the attribute "immune"
     */
    void setImmune(bool value);

    /**
     * \fn QTimer *getImmuneTimer() const;
     * \brief accessors for the "immuneTimer" attribute.
     * \param value of the attribute "immuneTimer"
     */
    QTimer *getImmuneTimer() const;

public slots:


    /**
     * \fn virtual void disableImmune();
     * \brief remove immunity
     */
    virtual void disableImmune();


protected :


    /**
     * \var  bool flying;
     * \brief true if the player is flying
     *
     */
    bool flying;

    /**
     * \var  bool flying;
     * \brief true if the player is falling
     *
     */
    bool falling;

    /**
     * \var  bool flying;
     * \brief true if the player is jumping
     *
     */
    bool jumping;

    /**
     * \var  bool flying;
     * \brief true if the player is fixed
     *
     */
    bool fixed;


    /**
     * \var  float yForce;
     * \brief the speed of movement vertically to the object
     *
     */
    float yForce;

    /**
     * \var  float xForce;
     * \brief the horizontal travel speed of the object
     *
     */
    float xForce;

    /**
     * \var  float xAcceleration;
     * \brief the horizontal travel speed of the object
     *
     */
    float xAcceleration;

    /**
     * \var int weight;
     * \brief the weight of the Object Unit
     *
     */
    int weight;


    /**
     * \var bool movingLeft;
     * \brief true if the objects is moving Left
     *
     */
    bool movingLeft;


    /**
     * \var bool movingRight;
     * \brief true if the objects is moving Right
     *
     */
    bool movingRight;

    /**
     * \var int maxSpeed;
     * \brief max speed of the objects Unit
     *
     */
    int maxSpeed;

    /**
     * \var bool alive;
     * \brief true if the objects Unit is alive
     *
     */
    bool alive;

    /**
     * \var int life;
     * \brief the value of the object's life
     *
     */
    int life;

    /**
     * \var bool immune;
     * \brief true if the objects is is immune
     *
     */
    bool immune;

    /**
     * \var QTimer * immuneTimer;
     * \brief The immunity timer
     *
     */
    QTimer * immuneTimer;


};

#endif // UNIT_H

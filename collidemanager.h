#ifndef COLLIDEMANAGER_H
#define COLLIDEMANAGER_H

#include "unit.h"
#include "QDebug"

struct fromPosition
{
    bool fromTop;
    bool fromUnder;
    bool fromRight;
    bool fromLeft;
};

/**
 * \file collidemanager.h
 * \brief Class allowing the collision of the objects of the class "player" with the class "element".
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
template <class itemType>
class CollideManager
{
public:

    /**
     * \fn CollideManager<itemType>(Unit * subject, bool solidTop, bool solidLeft, bool solidRight, bool solidUnder);
     * \brief Constructor of the CollideManager class
     * \param subject
     * \param solidTop
     * \param solidLeft
     * \param solidRight
     * \param solidUnder
     *
     * Retain the player's initial position before he moves
     */
    CollideManager<itemType>(Unit * subject, bool solidTop, bool solidLeft, bool solidRight, bool solidUnder);

    /**
     * \fn void updateCollidingPosition()
     * \brief adjusts the playing position of the subject if he comes in contact with a block.
     *
     *
     */
    void updateCollidingPosition();

    /**
     * \fn getAreColliding() const;
     * \brief Accessor of the attribute areColliding
     * \return the value of the attribute areColliding
     *
     */
    bool getAreColliding() const;

    /**
     * \fn QMap<itemType *, fromPosition> getCollidingItemList() const;
     * \brief Retrieve the elements in collison with the subject.
     * \return A list of elements in collison with the subject
     *
     */
    QMap<itemType *, fromPosition> getCollidingItemList() const;

private:
    Unit * subject;
    QMap<itemType *,fromPosition> collidingItemList;

    bool areColliding;

    bool solidTop;
    bool solidLeft;
    bool solidRight;
    bool solidUnder;

    int prec_y;
    int prec_x;
};

template<class itemType>
CollideManager<itemType>::CollideManager(Unit *subject, bool solidTop, bool solidLeft, bool solidRight, bool solidUnder)
{
    this->subject = subject;
    this->solidTop = solidTop;
    this->solidLeft = solidLeft;
    this->solidRight = solidRight;
    this->solidUnder = solidUnder;

    areColliding = false;

    prec_x = subject->x();
    prec_y = subject->y();
}

template<class itemType>
void CollideManager<itemType>::updateCollidingPosition()
{
    int next_x = subject->x();
    int next_y = subject->y();

    // get a list of all the items currently colliding with player
    QList<QGraphicsItem *> colliding_items = subject->collidingItems();
    QList<itemType *> collidingItemList;
    itemType * collidedItem = NULL;
    for(QGraphicsItem * item : colliding_items){
        itemType * specificItem = dynamic_cast<itemType *>(item);
        if(specificItem){
            collidingItemList.append(specificItem);
            areColliding = true;
        }
    }
    //qDebug() << "no "<< x() << y() << "prec : " << prec_x << prec_y;
    if (collidingItemList.count() > 0 && areColliding){
        for(int i = 0 ; i < collidingItemList.count() ; i ++){
            collidedItem = collidingItemList[i];

            // Bloc position
            int bloc_y = collidedItem->y();
            int bloc_x = collidedItem->x();

            //qDebug() << subjet->y() + subjet->getHeight() << subjet->x() ;
            // Last position
            bool fromTop = false;
            bool fromUnder = false;
            bool fromRight = false;
            bool fromLeft = false;

            if( prec_y + subject->getHeight() - 1 <= bloc_y)
                fromTop = true;
            if( prec_y - collidedItem->getHeight() >= bloc_y)
                fromUnder = true;
            if( prec_x + subject->getWidth() <= bloc_x)
                fromLeft = true;
            if( prec_x >= bloc_x + collidedItem->getWidth() )
                fromRight = true;

            fromPosition positions;
            positions.fromTop = fromTop;
            positions.fromLeft = fromLeft;
            positions.fromRight = fromRight;
            positions.fromUnder = fromUnder;
            this->collidingItemList.insert(collidedItem,positions);

            //qDebug() << "top:" <<fromTop << " under:" << fromUnder << " right" << fromRight << " left:" << fromLeft;
            //qDebug() << x() << y() << "prec : " << prec_x << prec_y;
            //qDebug() << speed;

            // Collide on the top
            if(solidTop &&
                    fromTop &&
                    !fromUnder &&
                    !fromRight &&
                    !fromLeft){
                // Adjust the position of the player exactly on the bloc
                next_y = bloc_y - subject->getHeight() + 1; // +1 to stay in touch with bloc
                subject->setYForce(0);
            }
            // Collide the south
            else if(solidUnder &&
                    subject->isJumping() &&
                    !fromTop &&
                    fromUnder &&
                    !fromRight &&
                    !fromLeft ){
                next_y = bloc_y + collidedItem->getHeight() ;
                subject->setYForce( - subject->getYForce() );
            }
            // Collide the right side
            else if(solidRight &&
                    !fromTop &&
                    !fromLeft &&
                    !fromUnder &&
                    fromRight ){
                // Adjust the position of the player exactly beside the bloc
                next_x = bloc_x + collidedItem->getWidth() + 1;
                subject->setXForce(0);
            }
            // Collide the left side
            else if(solidLeft &&
                    !fromTop &&
                    !fromRight &&
                    !fromUnder &&
                    fromLeft ){
                // Adjust the position of the player exactly beside the bloc
                next_x = bloc_x - subject->getWidth() - 1;
                subject->setXForce(0);
            }
            else if (collidingItemList.count() > 1){
                continue;   // if other collides exists, then its not realy a corner so we skip corner cases
            }
            // Collide top right corner
            else if ((solidTop || solidRight) && fromTop == true && fromRight == true){
                //next_y = bloc_y - subject->getHeight(); // +1 to stay in touch with bloc
                next_x = bloc_x + collidedItem->getWidth();
                //subject->setYForce(0);
                subject->setXForce(0);
            }
            // Collide top left corner
            else if ((solidTop || solidLeft) && fromTop == true && fromLeft == true){
                //next_y = bloc_y - subject->getHeight() + 2; // +1 to stay in touch with bloc
                next_x = bloc_x - subject->getWidth();
                //subject->setYForce(0);
                subject->setXForce(0);
            }
            //Collide bottom right corners
            else if ((solidUnder || solidRight) && fromUnder ==  true && fromRight == true && subject->isJumping() == true){
                next_y = bloc_y + collidedItem->getHeight() + 2;
                next_x = bloc_x + collidedItem->getWidth() + 1;
                subject->setYForce( - subject->getYForce());
            }
            //Collide bottom left corners
            else if ((solidUnder || solidLeft) && fromUnder ==  true && fromLeft == true && subject->isJumping() == true){
                next_y = bloc_y + collidedItem->getHeight() ;
                next_x = bloc_x - subject->getWidth() - 1;
                subject->setYForce( - subject->getYForce());
                subject->setXForce(0);
            }
            else{
                // reset speed
                //subject->setXForce(10);
            }
        }
        subject->setPos(next_x,next_y);
    }
}

template<class itemType>
bool CollideManager<itemType>::getAreColliding() const
{
    return areColliding;
}

template<class itemType>
QMap<itemType *, fromPosition> CollideManager<itemType>::getCollidingItemList() const
{
return collidingItemList;
}
#endif // COLLIDEMANAGER_H

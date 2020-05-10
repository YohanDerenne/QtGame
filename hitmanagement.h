#ifndef HITMANAGEMENT_H
#define HITMANAGEMENT_H

#include <QGraphicsPixmapItem>


template<typename itemType>
class HitManagement
{
public:
    HitManagement();

private:
    const QGraphicsPixmapItem Item;
    bool isTop = false;
    bool isUnder = false;
    bool isRight = false;
    bool isLeft = false;
};

#endif // HITMANAGEMENT_H

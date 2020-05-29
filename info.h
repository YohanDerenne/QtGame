#ifndef INFO_H
#define INFO_H

#include <QGraphicsItemGroup>
#include "configuration.h"
#include "lifeinfo.h"


class Info : public QGraphicsItemGroup
{
public:
    Info();

    LifeInfo *getLife() const;

    int getNbLife() const;

    void setNbLife(int value);

private:
    LifeInfo * life;
    QGraphicsRectItem * zone;
    int nbLife;
    QGraphicsTextItem * livesText;

};

#endif // INFO_H

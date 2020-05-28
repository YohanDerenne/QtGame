#ifndef INFO_H
#define INFO_H

#include <QGraphicsItemGroup>
#include "player.h"
#include "configuration.h"
#include "lifeinfo.h"


class Info : public QGraphicsItemGroup
{
public:
    Info();

private:
    LifeInfo * life;
    QGraphicsRectItem * zone;
    int nbLife;

};

#endif // INFO_H

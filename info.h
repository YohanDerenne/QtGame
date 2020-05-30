#ifndef INFO_H
#define INFO_H

#include <QGraphicsItemGroup>
#include "configuration.h"
#include "lifebar.h"

class Info : public QGraphicsItemGroup
{
public:
    Info();
    ~Info();

    void setNbLife(int value);
    void setMaskIndicator(bool state);

private:
    LifeBar * life;
    Element * maskIndicator;
};

#endif // INFO_H

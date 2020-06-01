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
    void setGelIndicator(bool state);

private:
    LifeBar * life;
    Element * maskIndicator;
    Element * gelIndicator;
    void updateIndicatorPos();
};

#endif // INFO_H

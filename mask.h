#ifndef MASK_H
#define MASK_H
#include "consoObject.h"
#include "configuration.h"


class Mask: public consoObject
{
public:
    Mask();
    void applyEffect(Unit * unit);

private:
    QTimer * bonusTimer;
};

#endif // MASK_H

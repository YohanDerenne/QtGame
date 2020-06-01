#ifndef HEART_H
#define HEART_H
#include "consoObject.h"
#include "configuration.h"



class Heart: public consoObject
{
public:
    Heart();
    void applyEffect(Unit * unit);
};

#endif // HEART_H

#ifndef GEL_H
#define GEL_H
#include "consoObject.h"
#include "configuration.h"

class Gel : public consoObject
{
public:
    Gel();
    void applyEffect(Unit * unit);
};

#endif // GEL_H

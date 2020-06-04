#ifndef MOBILEVIRUS_H
#define MOBILEVIRUS_H

#include "virus.h"

class MobileVirus : public Virus
{
public:
    MobileVirus();
    void switchSide();
};

#endif // MOBILEVIRUS_H

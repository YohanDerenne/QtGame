#ifndef FINISHFLAG_H
#define FINISHFLAG_H

#include "element.h"
#include "configuration.h"

/**
 * \file FinishFlag.h
 * \brief Victory flag class, inherits the "Element" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class FinishFlag : public Element
{
public:
    /**
     * \fn FinishFlag()
     * \brief Class FinishFlag Constructor
     * Reset the type to "finish" the width and height of the Flag with the parameters in the class Configuration.h
     */
    FinishFlag();
};

#endif // FINISHFLAG_H

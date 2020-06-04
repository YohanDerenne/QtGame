#ifndef MOBILEVIRUS_H
#define MOBILEVIRUS_H

#include "virus.h"

/**
 * \file mobilevirus.h
 * \brief Class of "Mobile Virus" type elements, inherits from the "Virus" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class MobileVirus : public Virus
{
public:
    /**
     * \fn MobileVirus()
     * \brief Constructor of the MobileVirus class
     * affects the item's type to "mobilevirus."
     */
    MobileVirus();

    /**
     * \fn switchSide()
     * @brief switch the side direction of the virus
     */
    void switchSide();
};

#endif // MOBILEVIRUS_H

#ifndef VIRUS_H
#define VIRUS_H

#include "unit.h"
#include "configuration.h"

/**
 * \file virus.h
 * \brief Class of the "Virus" element, inherits from the Unit class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Virus : public Unit
{
public:
    /**
     * \fn Projectile()
     * \brief Constructor of the Virus class
     * Initializes the default virus attributes
     */
    Virus();
};

#endif // VIRUS_H

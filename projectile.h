#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "unit.h"

/**
 * \file projectfile.h
 * \brief Projectile class, inherits the "Unit" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Projectile : public Unit
{
public:


    /**
     * \fn Projectile()
     * \brief Constructor of the Projectile class
     * Reset maxDist attribute to 1000
     */
    Projectile();

    virtual void touch(Unit *)=0;

    /**
     * \fn move()
     * \brief Moves the projectile
     */
    void move();

    /**
     * \fn isMaxDist()
     * \brief Check if the projectile is moving at maximum.
     */
    bool isMaxDist();

    /**
     * \fn  void setBegin(int value);
     * \brief Modification accessors for the "begin" attribute.
     * \param value, value to assign to the attribute begin
     *
     */
    void setBegin(int value);

private:
    int maxDist;
    int begin;
};

#endif // PROJECTILE_H

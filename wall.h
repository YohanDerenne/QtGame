#ifndef WALL_H
#define WALL_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "fixedblock.h"
#include "configuration.h"

/**
 * \file wall.h
 * \brief Class of the brick-type element within the map, inherited from the "FixedBlock" class.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Wall : public FixedBlock
{
public:
    Wall();
};

#endif // WALL_H

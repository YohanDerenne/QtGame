#ifndef WALL_H
#define WALL_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "fixedblock.h"
#include "configuration.h"

/**
 * \file wall.h
 * \brief Classe de l'element de type brique au sein de la map, herite de la classe "FixedBlock".
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Wall : public FixedBlock
{
public:
    Wall();
};

#endif // WALL_H

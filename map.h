#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "player.h"
#include "element.h"
#include "virus.h"


class Map
{
public:
    Map();
    ~Map();

    void generateMap1();
    bool readmap(QString directory);
    void clearMap();
    bool saveMap(QString directory);

    QList<Element *> * getElementList() const;
    QList<Unit *> * getUnitList() ;
    Player *getPlayer() const;
    QImage getBackground() const;
    int getWidth() const;
    int getHeight() const;
    void setBackground(const QImage &value);
    static QList<QString> getLevels();

private:
    QImage background;
    QString backgroundPath;
    Player * player;
    QList<Element *> * elementList;
    QList<Unit *> * unitList;

    int width;
    int height;
};

#endif // MAP_H

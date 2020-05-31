#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "player.h"
#include "element.h"
#include "virus.h"
#include "heart.h"
#include "mask.h"
#include "gel.h"



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
    QList<Unit *> * getUnitList() const;
    QList<consoObject *> * getConsoObjectList() const;
    Player *getPlayer() const;
    QImage getBackground() const;
    int getWidth() const;
    int getHeight() const;
    void setBackground(const QImage &value);
    static QList<QString> getLevels();

    QString getName() const;

    Info *getPlayerInfo() const;

private:
    QImage background;
    QString backgroundPath;
    Player * player;
    QList<Element *> * elementList;
    QList<Unit *> * unitList;
    QList<consoObject *> * consoObjectList;
    int width;
    int height;
    QString name;
    Info * playerInfo;
};

#endif // MAP_H

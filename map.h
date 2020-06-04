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
#include "projectile.h"
#include "finishflag.h"
#include "mobilevirus.h"



class Map
{
public:
    Map();
    ~Map();

    void generateMap1();
    void generateMap2();
    void generateMapBen();
    void generateCityWorld();
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

    QList<Projectile *> *getProjectileList() const;
    void generateWall(int height, int xPosition, int yPosition);
    void generateRoad(int length, int xPosition, int yPosition);
    void generateStairs(int length, int xPosition, int yPosition,bool isLeftEmpty);
    void generateU(int xLength,int yLengthLeft, int yLengthRight, int xPosition, int yPosition);
    void generateRectangle(int length,int height, int xPosition,int yPosition);
    void generateRoadVirus(int length, int xPosition, int yPosition);
    void generateItem(int xPosition, int yPosition,Element* obj);

    QString getMusic() const;
    int getDifficulty() const;

private:
    QImage background;
    QString backgroundPath;
    Player * player;
    QList<Element *> * elementList;
    QList<Unit *> * unitList;
    QList<consoObject *> * consoObjectList;
    QList<Projectile *> * projectileList;
    int width;
    int height;
    QString name;
    Info * playerInfo;
    QString musicPath;
    int difficulty;
};

#endif // MAP_H

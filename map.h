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


/**
 * \file map.h
 * \brief Class of the map.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Map
{
public:

    /**
     * \fn Map()
     * \brief Constructor of the Map class
     * initializes attributes of Map object
     */
    Map();
    /**
     * \fn ~Map()
     * \brief destructor of the Map class
     * removes all objects from the Map object
     */
    ~Map();

    /**
     * \fn generateMap1()
     * \brief generate the 1st map
     *
     */
    void generateMap1();
    /**
     * \fn generateMap1()
     * \brief generate the 2nd map
     *
     */
    void generateMap2();
  
    void generateMapBen();
    void generateCityWorld();

    /**
     * \fn void readmap(QString directory);
     * \brief Creates a map from a file
     * \param directory, the path of the file used to create the map
     *
     */
    bool readmap(QString directory);


    /**
     * \fn void clearMap();
     * \brief deletes all objects used to create the map
     * \param directory, the path of the file used to create the map
     *
     */
    void clearMap();


    /**
     * \fn bool saveMap(QString directory);
     * \brief save a map in a file
     * \param directory, the path of the file used to save the map
     *
     */
    bool saveMap(QString directory);

    /**
     * \fn  QList<Element *> * getElementList() const;
     * \brief accessors for the "elementList" attribute.
     * \return a QList<Element *>, value of elementList
     *
     */
    QList<Element *> * getElementList() const;

    /**
     * \fn  QList<Unit *> * getUnitList() const;
     * \brief accessors for the "unitList" attribute.
     * \return a QList<Unit *>, value of unitList
     *
     */
    QList<Unit *> * getUnitList() const;

    /**
     * \fn  QList<consoObject *> * getConsoObjectList() const;
     * \brief accessors for the "consoObjectList" attribute.
     * \return a QList<consoObject *>, value of consoObjectList
     *
     */
    QList<consoObject *> * getConsoObjectList() const;

    /**
     * \fn  Player *getPlayer() const;
     * \brief accessors for the "player" attribute.
     * \return a Player* , value of player
     *
     */
    Player *getPlayer() const;


    /**
     * \fn  QImage getBackground() const;
     * \brief accessors for the "background" attribute.
     * \return a QImage , value of background
     *
     */
    QImage getBackground() const;


    /**
     * \fn  int getWidth() const;
     * \brief accessors for the "width" attribute.
     * \return a int, value of width
     *
     */
    int getWidth() const;

    /**
     * \fn  int getHeight() const;
     * \brief accessors for the "height" attribute.
     * \return a int, value of height
     *
     */
    int getHeight() const;

    /**
     * \fn  QImage setBackground() const;
     * \brief Modification accessors for the "background" attribute.
     *
     */
    void setBackground(const QImage &value);

    /**
     * \fn  QList<QString> getLevels() const;
     * \brief  lists all levels
     * \return returns a list of levels
     *
     */
    static QList<QString> getLevels();

    /**
     * \fn  int getName() const;
     * \brief accessors for the "name" attribute.
     * \return a QString, value of name
     *
     */
    QString getName() const;

    /**
     * \fn  Info * getPlayerInfo() const;
     * \brief accessors for the "playerInfo" attribute.
     * \return a Info, value of playerInfo
     *
     */
    Info *getPlayerInfo() const;


    /**
     * \fn   QList<Projectile *> * getProjectileList() const;
     * \brief accessors for the "projectileList" attribute.
     * \return a  QList<Projectile *>, value of projectileList
     *
     */
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

    /**
     * \var QImage background;
     * \brief the background image of the game
     *
     */
    QImage background;

    /**
     * \var QString backgroundPath;
     * \brief the background path
     *
     */
    QString backgroundPath;

    /**
     * \var Player * player;
     * \brief the player of the map
     *
     */
    Player * player;

    /**
     * \var QList<Element *> * elementList;
     * \brief The list of the elements of the map
     *
     */
    QList<Element *> * elementList;

    /**
     * \var QList<Element *> * elementList;
     * \brief The list of the Unit of the map
     *
     */
    QList<Unit *> * unitList;

    /**
     * \var QList<Element *> * elementList;
     * \brief The consumables lists of the map
     *
     */
    QList<consoObject *> * consoObjectList;

    /**
     * \var QList<Element *> * elementList;
     * \brief The projectile lists of the map
     *
     */
    QList<Projectile *> * projectileList;

    /**
     * \var int width;
     * \brief the width of the map
     *
     */
    int width;

    /**
     * \var int height;
     * \brief the height of the map
     *
     */
    int height;


    /**
     * \var QString name;
     * \brief the name of the map
     *
     */
    QString name;

    /**
     * \var Info * playerInfo;
     * \brief The information of the player of the map
     *
     */
    Info * playerInfo;
    QString musicPath;
    int difficulty;
};

#endif // MAP_H

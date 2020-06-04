#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMutex>

/**
 * \file element.h
 * \brief Class of the basic structure of the elements in the map.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class Element :  public QObject, public QGraphicsPixmapItem
{
public:

    /**
     * \fn Element()
     * \brief Class Element Constructor
     *
     * Reset the length and width of the element to 0.
     */
    Element();
    /**
     * \fn Element(int height,int width)
     * \brief Class Element Constructor
     *
     * \param height the height of the element
     * \param width the width of the element
     * Initializes the length and width of the element with the values passed in parameter.
     */
    Element(int height,int width);

    /**
     * \fn int getWidth() const
     * \brief Accessor to the "Width" attribute.
     * \return The value of the Width attribute of the "Element" object.
     */
    int getWidth() const;
    /**
     * \fn  void setWidth(int value)
     * \brief Width attribute modification accessors.
     * \param value, value to assign to the Width attribute
     *
     */
    void setWidth(int value);

    /**
     * \fn int getHeight() const
     * \brief Accessor of the "Height" attribute.
     * \return The value of the Height attribute of the "Element" object.
     */
    int getHeight() const;
    /**
     * \fn  void setHeight(int value)
     * \brief Height attribute modification accessors.
     * \param value, value to assign to the Height attribute
     *
     */
    void setHeight(int value);

    void setSprite(QString ressource);

    /**
     * \fn QString getType() const
     * \brief Accessor of the "type" attribute.
     * \return Returns the attribute "type" of the object "Element" of type QString
     */
    QString getType() const;
    /**
     * \fn  void setType(const QString &value)
     * \brief Modification accessors for the "type" attribute.
     * \param value, value to be assigned to the attribute type
     *
     */
    void setType(const QString &value);

    /**
     * \fn int getSpawnX() const
     * \brief Accessor to the "spawnX" attribute.
     * \return Returns the "spawnX" attribute of the "Element" object of type int .
     */
    int getSpawnX() const;
    /**
     * \fn  void setSpawnX(int value);
     * \brief Modification accessors for the "spawnX" attribute.
     * \param value, value to assign to the attribute spawnX
     *
     */
    void setSpawnX(int value);


    /**
     * \fn int getSpawnY() const
     * \brief Accessor to the "spawnY" attribute..
     * \return Returns the "spawnY" attribute of the "Element" object of type int .
     */
    int getSpawnY() const;
    /**
     * \fn  void setSpawnY(int value);
     * \brief Modification accessors for the "spawnY" attribute.
     * \param value, value to assign to the attribute spawnY
     *
     */
    void setSpawnY(int value);

    /**
     * \fn  void respawn();
     * \brief Function for respawning an Element
     *
     */
    void respawn();

    /**
     * \fn  int getIsRightSide() const;
     * \brief Accessor of the attribute isRightSide
     * \return The value of the attribute isRightSide
     *
     */
    int getIsRightSide() const;

protected:

    /**
     * \var int width
     * \brief the width of the element
     *
     */
    int width;

    /**
     * \var int height
     * \brief the height of the element
     *
     */
    int height;

    /**
     * \var int isRightSide
     * \brief 1 if the element is on the right side, 0 otherwise
     *
     */
    int isRightSide;

    /**
     * \var QString type;
     * \brief the type of the element
     *
     */
    QString type;

    /**
     * \var int spawnX;
     * \brief the x position of the spawn of the element
     *
     */
    int spawnX;

    /**
     * \var int spawnY;
     * \brief the y position of the spawn of the element
     *
     */
    int spawnY;
};

#endif // ELEMENT_H

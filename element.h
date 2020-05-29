#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMutex>

class Element :  public QGraphicsPixmapItem
{
public:
    Element();

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    void setSprite(QString ressource);

    QString getType() const;
    void setType(const QString &value);

    int getSpawnX() const;
    void setSpawnX(int value);

    int getSpawnY() const;
    void setSpawnY(int value);

    void respawn();

protected:
    int width;
    int height;
    int isRightSide;
    QString type;

    int spawnX;
    int spawnY;
};

#endif // ELEMENT_H

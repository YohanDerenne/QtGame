#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMutex>

class Element : public QGraphicsPixmapItem
{
public:
    Element();

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    void setSprite(QString ressource);

protected:
    int width;
    int height;
    int isRightSide;


};

#endif // ELEMENT_H

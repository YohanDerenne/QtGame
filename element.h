#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Element : public QGraphicsPixmapItem
{
public:
    Element();

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

protected:
    int width;
    int height;
};

#endif // ELEMENT_H

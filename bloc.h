#ifndef BLOC_H
#define BLOC_H
#include <QGraphicsPixmapItem>
#include <QObject>

class Bloc : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bloc();
};

#endif // BLOC_H

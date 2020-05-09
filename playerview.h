#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class PlayerView : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    PlayerView(QGraphicsItem * parent=0);
    void Jump();
    void SetMovingRight(bool state);
    void SetMovingLeft(bool state);

public slots:
    void MovePlayer();

private :
    bool flying;
    bool falling;
    bool jumping;
    float yAccel;
    float xAccel;
    int weight;

    bool movingLeft;
    bool movingRight;
    int speed;
};

#endif // PLAYERVIEW_H

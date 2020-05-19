#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <qscrollbar.h>
#include <QGraphicsPixmapItem>

#include "collidemanager.h"
#include "player.h"
#include "element.h"
#include "map.h"
#include "wall.h"
#include "configuration.h"



class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    ~Game();

    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void updatePlayerPosition();
    void respawn();

public slots:
    void updatePositions();

private:
    QGraphicsScene * scene;
    Player * player;
    QImage background;
    QList<Element *> elementList;
    QList<consoObject *> consoObjectList;
    Map * map;

    int windowWidth;
    int windowHeight;

};


#endif // GAME_H

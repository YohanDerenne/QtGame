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
#include <QThreadPool>


class GameEngine: public QGraphicsView{
    Q_OBJECT
    QThread workerThread;

public:
    GameEngine();
    ~GameEngine();

    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void updatePlayerPosition();
    void respawn();

    void updateCamera();

    Player *getPlayer() const;

    QMutex mutex;

public slots:
    void updatePositions();
    void animate();

private:
    QGraphicsScene * scene;
    Player * player;
    QImage background;
    QList<Element *> elementList;
    Map * map;

    int windowWidth;
    int windowHeight;

    int playerSprite;
    int playerStaticCounter;

signals:
    void operate(const QString&);

};


#endif // GAME_H

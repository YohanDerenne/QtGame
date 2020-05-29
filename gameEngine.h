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
#include <QSignalMapper>

#include "collidemanager.h"
#include "player.h"
#include "element.h"
#include "map.h"
#include "wall.h"
#include "configuration.h"
#include "info.h"
#include "menu.h"


class GameEngine: public QGraphicsView{
    Q_OBJECT

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

    void drawElements();

    void createVirus();
    void openMenu();
    void openGame();
    void clearLevel();

public slots:
    void updatePositions();
    void animate();
    void loadMap(QString worldName);

private:
    QGraphicsScene * levelScene;
    Player * player;
    QImage background;
    Map * map;

    int windowWidth;
    int windowHeight;

    int playerSprite;
    int playerStaticCounter;

    Info * playerInfo;

    QGraphicsItemGroup * worldPlan;

    Menu * menuScene;

    QTimer * Animtimer;
    QTimer * refreshTimer;

    QSignalMapper * buttonMenuMapper;

};


#endif // GAME_H

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
#include <QApplication>
#include <QGraphicsProxyWidget>

#include "collidemanager.h"
#include "player.h"
#include "element.h"
#include "map.h"
#include "wall.h"
#include "configuration.h"
#include "info.h"
#include "menu.h"
#include "pausegroup.h"



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
    void drawElements();

    void createVirus();

    void openGame();
    void openPause();

    void clearLevel();

public slots:
    void updatePositions();
    void animate();
    void loadMap(QString worldName);
    void closePause();
    void openMenu();
    void quitApp();

private:
    QGraphicsScene * levelScene;
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

    PauseGroup * pauseMenu;

    QGraphicsProxyWidget * continueProxy;
    QGraphicsProxyWidget * backMenuProxy;

    bool paused;

};


#endif // GAME_H

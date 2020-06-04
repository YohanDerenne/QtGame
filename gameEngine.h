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
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSoundEffect>

#include "collidemanager.h"
#include "player.h"
#include "element.h"
#include "map.h"
#include "wall.h"
#include "configuration.h"
#include "info.h"
#include "menu.h"
#include "pausegroup.h"
#include "projectile.h"
#include "gelprojectile.h"
#include "victorygroup.h"



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
    void updateProjectilePosition();
    void updateMobileVirusPosition();

    void createVirus();

    void openGame();
    void openPause();

    void clearLevel();

    void gameOver();

    void pauseTimer();
    void resumeTimer();

    void victory();
    void closeVictory();

    void playMusic(QString qrcPath);

public slots:
    void updateAllPositions();
    void loadMap(QString worldName);
    void animate();
    void retryMap();
    void closePause();
    void openMenu();
    void quitApp();
    void restart();

private:
    QGraphicsScene * levelScene;
    QImage background;
    Map * map;

    int windowWidth;
    int windowHeight;

    int playerSprite;
    int playerStaticCounter;

    QGraphicsItemGroup * worldPlan;

    Menu * menuScene;

    QTimer * Animtimer;
    QTimer * refreshTimer;
    QTimer * restartTimer;

    QSignalMapper * buttonMenuMapper;

    PauseGroup * pauseMenu;
    VictoryGroup * victoryMenu;

    QGraphicsProxyWidget * continueProxy;
    QGraphicsProxyWidget * backMenuProxy;

    bool paused;
    bool finished;

    int animFireDuration;

    bool spacePressed;

    int overRemainTime;
    int maskRemainTime;
    int gelRemainTime;
    int immuneRemainTime;

    QMediaPlayer * musicPlayer;
    QSoundEffect gain;
    QSoundEffect jump;
    QSoundEffect fire;
    QSoundEffect win;
    QSoundEffect hurt;
    QSoundEffect pause;
    QSoundEffect kick;
    QSoundEffect life;
};


#endif // GAME_H

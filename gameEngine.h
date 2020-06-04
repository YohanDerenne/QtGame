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


/**
 * \file GameEngine.h
 * \brief Class of the game engine.
 * \author Derenne / Kiavoukiladioko / Vouillon / Akrafi
 *
 */
class GameEngine: public QGraphicsView{
    Q_OBJECT

public:
    /**
     * \fn GameEngine()
     * \brief Constructor of the GameEngine class
     * initializes game
     */
    GameEngine();
    /**
     * \fn ~GameEngine()
     * \brief destructor of the GameEngine class
     * removes all objects from the game
     */
    ~GameEngine();

    /**
     * \fn void keyPressEvent(QKeyEvent * event) override;
     * \brief makes the player's moves
     */
    void keyPressEvent(QKeyEvent * event) override;

    /**
     * \fn void keyReleaseEvent(QKeyEvent * event) override;
     * \brief retrieves the keys that are pressed during the game
     */
    void keyReleaseEvent(QKeyEvent *event) override;

    /**
     * \fn void resizeEvent(QResizeEvent *event) override;
     * \brief is triggered when you change the size of the window,
     * it allows you to keep the map scaled according to the size of the window.
     */
    void resizeEvent(QResizeEvent *event) override;

    /**
     * \fn updatePlayerPosition();
     * \brief updates the player's position during the game
     */
    void updatePlayerPosition();

    /**
     * \fn respawn();
     * \brief respawn the player at the beginning of the game
     */
    void respawn();

    /**
     * \fn updateCamera();
     * \brief updates the camera position during the game
     */
    void updateCamera();

    /**
     * \fn drawElements();
     * \brief displays all elements
     */
    void drawElements();

    /**
     * \fn updateProjectilePosition();
     * \brief updates the projectile's position during the game
     */
    void updateProjectilePosition();

    /**
     * \fn updateMobileVirusPosition();
     * \brief updates all mobile virus position during the game
     */
    void updateMobileVirusPosition();

    /**
     * \fn createVirus();
     * \brief creates a virus within the map
     */
    void createVirus();

    /**
     * \fn openGame();
     * \brief start the game
     */
    void openGame();
    /**
     * \fn openPause();
     * \brief pauses the game
     */
    void openPause();

    /**
     * \fn clearLevel();
     * \brief deletes the objects used to create a level
     */
    void clearLevel();

    /**
     * \fn gameOver();
     * \brief is playing a game over
     */
    void gameOver();


    /**
     * \fn pauseTimer();
     * \brief sets the timer for the pause menu
     */
    void pauseTimer();
    /**
     * \fn resumeTimer();
     * \brief restart the game after a pause
     */
    void resumeTimer();

    /**
     * \fn victory();
     * \brief is playing a victory menu
     */
    void victory();

    /**
     * \fn closeVictory();
     * \brief closes the victory menu
     */
    void closeVictory();

    /**
     * \fn void playMusic(QString qrcPath);
     * \brief play a music
     */
    void playMusic(QString qrcPath);

public slots:

    /**
     * \fn updateAllPositions();
     * \brief update all element's position
     */
    void updateAllPositions();
    /**
     * \fn loadMap(QString worldName);
     * \brief the level to be charged
     * \param worldName,
     */
    void loadMap(QString worldName);

    /**
     * \fn animate();
     * \brief makes the animations
     */
    void animate();
    /**
     * \fn retryMap();
     * \brief reload the map
     */
    void retryMap();

    /**
     * \fn closePause();
     * \brief remove the pause mode
     */
    void closePause();

    /**
     * \fn openMenu();
     * \brief opens the menu
     */
    void openMenu();


    /**
     * \fn quitApp();
     * \brief quit the game
     */
    void quitApp();

    /**
     * \fn restart();
     * \brief restart the game
     */
    void restart();

private:

    /**
     * \var QGraphicsScene * levelScene;
     * \brief the scene of the game
     *
     */
    QGraphicsScene * levelScene;
    /**
     * \var QImage background;
     * \brief the background image of the game
     *
     */
    QImage background;
    /**
     * \var Map * map;
     * \brief the map of the game
     *
     */
    Map * map;

    /**
     * \var int windowWidth;
     * \brief the width of the window
     *
     */
    int windowWidth;
    /**
     * \var Map * map;
     * \brief the height of the window
     *
     */
    int windowHeight;


    /**
     * \var int playerSprite;
     * \brief sprite number for animation
     *
     */
    int playerSprite;

    /**
     * \var int playerStaticCounter;
     * \brief counter that allows to manage the blinking of the character's eyes when he is motionless
     *
     */
    int playerStaticCounter;

    /**
     * \var QGraphicsItemGroup * worldPlan
     * \brief contains several items that move and are not fixed
     *
     */
    QGraphicsItemGroup * worldPlan;

    /**
     * \var Menu * menuScene;
     * \brief the main menu of the game
     *
     */
    Menu * menuScene;

    /**
     * \var QTimer * Animtimer;
     * \brief Timer to manage animations
     *
     */
    QTimer * Animtimer;

    /**
     * \var QTimer * refreshTimer;
     * \brief the number of frames per second
     *
     */
    QTimer * refreshTimer;

    /**
     * \var QTimer * restartTimer;
     * \brief the delay before respawn
     *
     */
    QTimer * restartTimer;


    /**
     * \var QSignalMapper * buttonMenuMapper;
     * \brief mapping of the menu buttons
     *
     */
    QSignalMapper * buttonMenuMapper;

    /**
     * \var PauseGroup * pauseMenu;
     * \brief The pause menu of the game
     *
     */
    PauseGroup * pauseMenu;

    /**
     * \var VictoryGroup * victoryMenu;
     * \brief The victory menu of the game
     *
     */
    VictoryGroup * victoryMenu;

    /**
     * \var QGraphicsProxyWidget * continueProxy;
     * \brief use to delete widgets on scenes button continues
     *
     */
    QGraphicsProxyWidget * continueProxy;

    /**
     * \var QGraphicsProxyWidget * backMenuProxy;
     * \brief use to remove widgets on back button scenes
     *
     */
    QGraphicsProxyWidget * backMenuProxy;

    /**
     * \var bool paused;
     * \brief true if the game is paused
     *
     */
    bool paused;
    /**
     * \var bool finished;
     * \brief true if the game is finished
     *
     */
    bool finished;

    /**
     * \var int animFireDuration;
     * \brief time of the animation during the throwing of the projectile
     *
     */
    int animFireDuration;

    /**
     * \var bool spacePressed;
     * \brief true if the space bar is pressed
     *
     */
    bool spacePressed;

    /**
     * \var int overRemainTime;
     * \brief time left for a timer when you take a break.
     *
     */
    int overRemainTime;

    /**
     * \var int maskRemainTime;
     * \brief time remaining for a mask
     *
     */
    int maskRemainTime;

    /**
     * \var int gelRemainTime;
     * \brief time remaining for a gel
     *
     */
    int gelRemainTime;

    /**
     * \var int immuneRemainTime;
     * \brief time remaining for immininity
     *
     */
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

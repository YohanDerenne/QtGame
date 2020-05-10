#include "game.h"
#include "bloc.h"
#include "configuration.h"
#include <QDebug>
#include <QKeyEvent>
#include <qscrollbar.h>
#include <QGraphicsPixmapItem>

Game::Game(QWidget *parent)
{
    ratio = 1;

    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,MAP_WIDTH,MAP_HEIGHT);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);

    // set background
    background = QImage(":/ressources/images/background.jpg");
    QImage background_resized = background.scaledToHeight(WINDOW_HEIGHT);
    setBackgroundBrush(QBrush(background_resized));

    // create the player
    player = new PlayerView();
    player->setPos(200,400);

    // add the player to the scene
    scene->addItem(player);

    // create map
    // floor
    for(int i = 0; i < 15; i++){
        Bloc * bloc = new Bloc();
        bloc->setPos(i*BLOC_SIZE,500);
        scene->addItem(bloc);
    }
    // platform
    for(int i = 0; i < 5; i++){
        if(i != 3){
            Bloc * bloc = new Bloc();
            bloc->setPos(i*BLOC_SIZE + 200 ,300);
            scene->addItem(bloc);
        }
    }
    /*
    // roof
    for(int i = 0; i < 9; i++){
         Bloc * bloc = new Bloc();
         bloc->setPos(i*BLOC_SIZE + 50 ,300);
         scene->addItem(bloc);
    }
    */
    // wall
    for(int i = 5; i >= 0; i--){
        if(i != 2 && i !=3 ){
            Bloc * bloc = new Bloc();
            bloc->setPos(0 ,500 - BLOC_SIZE - i * BLOC_SIZE);
            scene->addItem(bloc);
        }

    }
    // little wall
    for(int i = 3; i >= 0; i--){
        Bloc * bloc = new Bloc();
        bloc->setPos(500 ,500 - BLOC_SIZE - i * BLOC_SIZE);
        scene->addItem(bloc);
    }

    //show();
    horizontalScrollBar()->setValue(1);
    verticalScrollBar()->setValue(1);
}

Game::~Game()
{
    qDebug() << "delete";
    scene->clear();
    delete player;
    delete scene;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "key pressed" ;
    if (event->key() == Qt::Key_Left){
        //horizontalScrollBar()->setValue(horizontalScrollBar()->value() - 10);
        player->SetMovingLeft(true);
    }
    else if (event->key() == Qt::Key_Right){
        //horizontalScrollBar()->setValue(horizontalScrollBar()->value() + 10);
        player->SetMovingRight(true);
    }
    else if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Up){
        player->Jump();
    }
    else if (event->key() == Qt::Key_R){
        player->setPos(200,200);
    }
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "key released" ;
    if (event->key() == Qt::Key_Left){
        player->SetMovingLeft(false);
    }
    else if (event->key() == Qt::Key_Right){
        player->SetMovingRight(false);
    }
}

void Game::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resize";
    QRect rect = QRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    fitInView(rect);
}


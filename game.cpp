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
    player->setPos(200,200);

    // add the player to the scene
    scene->addItem(player);

    // create map
    for(int i = 0; i < 10; i++){
         Bloc * bloc = new Bloc();
         bloc->setPos(i*BLOC_SIZE,500);
         scene->addItem(bloc);
    }

    for(int i = 0; i < 10; i++){
         Bloc * bloc = new Bloc();
         bloc->setPos(i*BLOC_SIZE + 400 ,200);
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


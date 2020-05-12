#include "game.h"
#include "wall.h"
#include "configuration.h"
#include <QDebug>
#include <QKeyEvent>
#include <qscrollbar.h>
#include <QGraphicsPixmapItem>
#include <element.h>
#include <QDebug>
#include <QTimer>

Game::Game()
{
    windowWidth = WINDOW_WIDTH;
    windowHeight = WINDOW_HEIGHT;
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,MAP_WIDTH,MAP_HEIGHT);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);

    // create map
    map = new Map();
    map->readExample();

    // set scene background
    //setBackgroundBrush(QImage(map->getBackground()));
    this->setBackgroundBrush(QImage(map->getBackground()));


    // set player
    player = map->getPlayer();
    scene->addItem(player);

    // set elements
    for(Element * element : map->getElementList()){
        scene->addItem(element);
    }

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updatePositions()));
    // start the timer
    timer->start(1000/FPS);

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

void Game::updatePlayerPosition()
{
    player->updateMovementStates();

    int prec_x = player->x();
    int prec_y = player->y();
    int next_x = player->x();
    int next_y = player->y();
    /*
    // if collinding
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(colliding_items[i]) != typeid(Bloc)){
            int bloc_y = colliding_items[i]->y();
            // Top
            if(falling == true && (bloc_y - next_x) < 10){
                next_y = bloc_y - PLAYER_HEIGHT;
                yAccel = -100;
            }
            falling = false;
        }
    }*/
    if(player->isFlying() == true){
        next_y += player->getYForce() * 1/FPS;
        float dt = 1/(float)FPS;
        player->setYForce( player->getYForce() + player->getWeight() * 9 * dt);
    }
    if(player->isMovingLeft()){
        next_x -= player->getSpeed();
    }
    if(player->isMovingRight()){
        next_x += player->getSpeed();
    }

    player->setPos(next_x,next_y);
    // get a list of all the items currently colliding with player
    QList<QGraphicsItem *> colliding_items = player->collidingItems();
    QList<QGraphicsItem *> colliding_blocs;
    QGraphicsItem * collidedBloc = NULL;
    for(QGraphicsItem * item : colliding_items){
        if(typeid(item) != typeid(Wall)){
            colliding_blocs.append(item);
        }
    }
    //qDebug() << "no "<< x() << y() << "prec : " << prec_x << prec_y;
    if (colliding_blocs.count() > 0){
        for(int i = 0 ; i < colliding_blocs.count() ; i ++){
            collidedBloc = colliding_blocs[i];

            // Bloc position
            int bloc_y = collidedBloc->y();
            int bloc_x = collidedBloc->x();

            //qDebug() << (y() + PLAYER_HEIGHT) << " -" << bloc_y ;
            // Last position
            bool isTop = false;
            bool isUnder = false;
            bool isRight = false;
            bool isLeft = false;
            if( prec_y + player->getHeight() - 1 <= bloc_y)
                isTop = true;
            if( prec_y - BLOC_SIZE >= bloc_y)
                isUnder = true;
            if( prec_x + PLAYER_WIDTH <= bloc_x)
                isLeft = true;
            if( prec_x >= bloc_x + BLOC_SIZE )
                isRight = true;

            //qDebug() << "top:" <<isTop << " under:" << isUnder << " right" << isRight << " left:" << isLeft;
            //qDebug() << x() << y() << "prec : " << prec_x << prec_y;
            //qDebug() << speed;
            // falling on a top of a bloc case
            if(isTop == true && isUnder == false && isRight == false && isLeft == false){
                // Adjust the position of the player exactly on the bloc
                next_y = bloc_y - PLAYER_HEIGHT + 1; // +1 to stay in touch with bloc
                player->setYForce(0);
            }


            // Collide the south of a bloc
            else if(player->isJumping() == true && isTop == false && isUnder == true && isRight == false && isLeft == false){
                next_y = bloc_y + BLOC_SIZE ;
                player->setYForce( - player->getYForce() );
            }
            //qDebug() << isTop << isUnder;
            // Collide the right side of a bloc
            else if(isTop == false && isLeft == false && isUnder == false && isRight == true){
                // Adjust the position of the player exactly beside the bloc
                next_x = bloc_x + BLOC_SIZE + 1;
            }
            // Collide the left side of a bloc
            else if(isTop == false && isRight == false && isUnder == false && isLeft == true){
                // Adjust the position of the player exactly beside the bloc
                next_x = bloc_x - PLAYER_WIDTH - 1;
            }
            else if (colliding_blocs.count() > 1){
                continue;   // if other collides exists, then its not realy a corner so we skip corner cases
            }
            // Collide top right corner
            else if (isTop == true && isRight == true){
                next_y = bloc_y - PLAYER_HEIGHT; // +1 to stay in touch with bloc
                next_x = bloc_x + BLOC_SIZE + 1;
                player->setYForce(0);
            }
            // Collide top left corner
            else if (isTop == true && isLeft == true){
                next_y = bloc_y - PLAYER_HEIGHT; // +1 to stay in touch with bloc
                next_x = bloc_x - PLAYER_WIDTH - 1;
                player->setYForce(0);
            }
            //Collide bottom right corners
            else if (isUnder ==  true && isRight == true && player->isJumping() == true){
                next_y = bloc_y + BLOC_SIZE ;
                next_x = bloc_x + BLOC_SIZE + 1;
                player->setYForce( - player->getYForce());
            }
            //Collide bottom left corners
            else if (isUnder ==  true && isLeft == true && player->isJumping() == true){
                next_y = bloc_y + BLOC_SIZE ;
                next_x = bloc_x - PLAYER_WIDTH - 1;
                player->setYForce( - player->getYForce());
            }
            else{
                // reset speed
                player->setSpeed(10);
            }
        }
        player->setPos(next_x,next_y);
    }
    else{
        // inital falling
        if(player->getYForce() == 0)
            player->setYForce(player->getYForce() + 100);
        player->setSpeed(10);
    }
}

void Game::updatePositions()
{
    updatePlayerPosition();
}


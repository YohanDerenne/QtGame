#include "playerview.h"
#include "bloc.h"
#include "configuration.h"
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

PlayerView::PlayerView(QGraphicsItem *parent)
{
    // set graphic
    QPixmap img = QPixmap(":/ressources/images/player.png");
    img = img.scaled(PLAYER_WIDTH,PLAYER_HEIGHT);
    setPixmap(img);

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    // Physics
    flying = false;
    movingLeft = false;
    movingRight = false;
    falling = false;
    jumping = false;
    speed = 10;
    weight = 200;
    yAccel = 0;
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MovePlayer()));
    // start the timer
    timer->start(1000/FPS);
}

void PlayerView::Jump()
{
    if(flying == false){
        setPos(x(),y() - 10);
        yAccel = -800;
        flying = true;
        jumping = true;
    }
}

void PlayerView::SetMovingRight(bool state)
{
    movingRight = state;
}

void PlayerView::SetMovingLeft(bool state)
{
    movingLeft = state;
}

void PlayerView::MovePlayer()
{

    if(yAccel > 0 )
        falling = true;
    else
        falling = false;

    if(yAccel < 0){
        jumping = true;
    }
    else{
        jumping = false;
    }
    if(yAccel == 0){
        flying = false;
    }
    else{
        flying = true;
    }


    int prec_x = x();
    int prec_y = y();
    int next_x = x();
    int next_y = y();
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
    if(flying == true){
        next_y += yAccel * 1/FPS;
        float dt = 1/(float)FPS;
        yAccel = yAccel + weight * 9 * dt;
    }
    if(movingLeft){
        next_x -= speed;
    }
    if(movingRight){
        next_x += speed;
    }

    setPos(next_x,next_y);
    // get a list of all the items currently colliding with player
    QList<QGraphicsItem *> colliding_items = this->collidingItems();
    QList<QGraphicsItem *> colliding_blocs;
    QGraphicsItem * collidedBloc = NULL;
    for(QGraphicsItem * item : colliding_items){
        if(typeid(item) != typeid(Bloc)){
            colliding_blocs.append(item);
        }
    }

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
            if( prec_y + PLAYER_HEIGHT - 1 <= bloc_y)
                isTop = true;
            if( prec_y - BLOC_SIZE >= bloc_y)
                isUnder = true;
            if( prec_x + PLAYER_WIDTH <= bloc_x)
                isLeft = true;
            if( prec_x >= bloc_x + BLOC_SIZE )
                isRight = true;

            qDebug() << "top:" <<isTop << " under:" << isUnder << " right" << isRight << " left:" << isLeft;
            //qDebug() << x() << y() << "prec : " << prec_x << prec_y;
            qDebug() << speed;
            // falling on a top of a bloc case
            if(isTop == true && isUnder == false && isRight == false && isLeft == false){
                // Adjust the position of the player exactly on the bloc
                next_y = bloc_y - PLAYER_HEIGHT + 1; // +1 to stay in touch with bloc
                falling = false;
                yAccel = 0;
            }


            // Collide the south of a bloc
            else if(jumping == true && isTop == false && isUnder == true && isRight == false && isLeft == false){
                next_y = bloc_y + BLOC_SIZE ;
                yAccel = -yAccel;
                jumping = false;
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
                continue;
            }
            // Collide top right corner
            else if (isTop == true && isRight == true){
                next_y = bloc_y - PLAYER_HEIGHT; // +1 to stay in touch with bloc
                next_x = bloc_x + BLOC_SIZE + 1;
                yAccel = 0;
            }
            // Collide top left corner
            else if (isTop == true && isLeft == true){
                next_y = bloc_y - PLAYER_HEIGHT; // +1 to stay in touch with bloc
                next_x = bloc_x - PLAYER_WIDTH - 1;
                yAccel = 0;
            }
            //Collide bottom right corners
            else if (isUnder ==  true && isRight == true && jumping == true){
                next_y = bloc_y + BLOC_SIZE ;
                next_x = bloc_x + BLOC_SIZE + 1;
                yAccel = -yAccel;
                jumping = false;
            }
            //Collide bottom left corners
            else if (isUnder ==  true && isLeft == true && jumping == true){
                next_y = bloc_y + BLOC_SIZE ;
                next_x = bloc_x - PLAYER_WIDTH - 1;
                yAccel = -yAccel;
                jumping = false;
            }
            else{
                // reset speed
                speed = 10;
            }
        }
        setPos(next_x,next_y);
    }
    else{
        // no bloc colliding -> falling or continue force movement
        if(yAccel == 0)
            yAccel -= 1;
        //        next_y += yAccel * 1/FPS;
        //        float dt = 1/(float)FPS;
        //        yAccel = yAccel + weight * 9 * dt;
        speed = 10;
    }
}



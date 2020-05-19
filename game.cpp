#include "game.h"

// for test only
void createVirus(QGraphicsScene* scene);
void createLife(QGraphicsScene* scene);

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

    //set consoObject
    for(consoObject * object : map->getConsoObjectList()){
        scene->addItem(object);
    }

    // set mobs
    for(Unit * unit : map->getUnitList()){
        scene->addItem(unit);
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
        respawn();
    }
    else if (event->key() == Qt::Key_A){
        createVirus(scene);

    }
    else if(event->key() == Qt::Key_L){
        createLife(scene);
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

    CollideManager<FixedBlock> * wallCollider = new CollideManager<FixedBlock>(player,true,true,true,true);
    CollideManager<Virus> * virusCollider = new CollideManager<Virus>(player,true,false,false,false);
    CollideManager<life> * lifeCollider = new CollideManager<life>(player,true,false,false,false);

    int next_x = player->x();
    int next_y = player->y();

    // Moving the player
    if(player->isFlying() == true){
        next_y += player->getYForce() * 1/FPS;
        float dt = 1/(float)FPS;
        player->setYForce( player->getYForce() + player->getWeight() * GRAVITY * dt);
    }
    if(player->isMovingLeft()){
        player->increaseLeftForce();
    }
    else if(player->isMovingRight()){
        player->increaseRightForce();
    }
    else {
        player->decreaseXForce();
    }
    next_x += player->getXForce();
    player->setPos(next_x,next_y);

    wallCollider->updateCollidingPosition();
    virusCollider->updateCollidingPosition();
    lifeCollider->updateCollidingPosition();

    // If no collides -> begin de falling
    if(!wallCollider->getAreColliding() &&
            !virusCollider->getAreColliding()){
        if(player->getYForce() == 0)
            player->setYForce(player->getYForce() + 100);
        //player->setXForce(10);
    }

    // If no collides -> begin de falling
    if(!wallCollider->getAreColliding() &&
            !lifeCollider->getAreColliding()){
        if(player->getYForce() == 0)
            player->setYForce(player->getYForce() + 100);
        //player->setXForce(10);
    }

    if(virusCollider->getAreColliding()){
        QMap<Virus *,fromPosition> virusInfo = virusCollider->getCollidingItemList();
        QMapIterator<Virus*, fromPosition> iterator(virusInfo);
        while (iterator.hasNext()) {
            iterator.next();
            if(iterator.value().fromTop == true){
                // rebondi
                player->setYForce(-100);

                // Kill virus
                delete iterator.key();
                elementList.removeOne(iterator.key());
            }
            else{
                respawn();
            }
        }
    }
    //life
    if(lifeCollider->getAreColliding()){
        QMap<life *,fromPosition> lifeInfo = lifeCollider->getCollidingItemList();
        QMapIterator<life*, fromPosition> iterator(lifeInfo);
        while (iterator.hasNext()) {
            iterator.next();
            if(iterator.value().fromTop == true){
                // rebondi
                player->setYForce(-100);

                // delete lifegame
                delete iterator.key();
                consoObjectList.removeOne(iterator.key());
            }
            else{
                respawn();
            }
        }
    }

    delete wallCollider;
    delete virusCollider;
    delete lifeCollider;
    //qDebug() << player->getXForce();
}

void Game::respawn()
{
    player->setPos(200,400);
}

void Game::updatePositions()
{
    updatePlayerPosition();
}

// FOR TESTS
void createVirus(QGraphicsScene* scene){
    Virus * virus = new Virus();
    virus->setPos(700,450);
    scene->addItem(virus);
}

void createLife(QGraphicsScene* scene){

    life *l = new life();
    l->setPos(700,450);
    scene->addItem(l);
}

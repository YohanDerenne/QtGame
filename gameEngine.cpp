#include "gameEngine.h"


// for test only
void createVirus(QGraphicsScene* scene);

GameEngine::GameEngine()
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
    map->generateMap1();
    //drawElements();
    map->saveMap("world_1");
    map->readmap("world_1");
    drawElements();


    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updatePositions()));
    // start the timer
    timer->start(1000/FPS);


    QTimer * Animtimer = new QTimer(this);
    connect(Animtimer,SIGNAL(timeout()),this,SLOT(animate()));
    // start the timer
    Animtimer->start(90);

    //show();
    horizontalScrollBar()->setValue(0);
    verticalScrollBar()->setValue(0);
    //horizontalScrollBar()->setMinimum(0);
    //horizontalScrollBar()->setMaximum(map->getWidth() + WINDOW_WIDTH);
    horizontalScrollBar()->setPageStep(0);
    playerSprite = 1;
    playerStaticCounter = 1;

    // Info
    playerInfo = new Info();
    scene->addItem(playerInfo);

    //horizontalScrollBar()->setRange(0,MAP_WIDTH);
}

GameEngine::~GameEngine()
{
    qDebug() << "delete";
    scene->clear();
    delete player;
    delete scene;


}

void GameEngine::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "key pressed" ;
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
}

void GameEngine::keyReleaseEvent(QKeyEvent *event)
{
    //qDebug() << "key released" ;
    if (event->key() == Qt::Key_Left){
        player->SetMovingLeft(false);
    }
    else if (event->key() == Qt::Key_Right){
        player->SetMovingRight(false);
    }
}

void GameEngine::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resize";
    QRect rect = QRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    fitInView(rect);
}

void GameEngine::updatePlayerPosition()
{
    player->updateMovementStates();

    CollideManager<FixedBlock> * wallCollider = new CollideManager<FixedBlock>(player,true,true,true,true);
    CollideManager<Virus> * virusCollider = new CollideManager<Virus>(player,true,false,false,false);

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

    // If no collides -> begin de falling
    if(!wallCollider->getAreColliding() &&
            !virusCollider->getAreColliding()){
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

    delete wallCollider;
    delete virusCollider;
    //qDebug() << player->getXForce();
}

void GameEngine::respawn()
{
    player->setPos(200,400);
}

void GameEngine::updateCamera()
{
    float coef = (float) horizontalScrollBar()->maximum() / (float) (MAP_WIDTH - WINDOW_WIDTH);

    // The player is too close to the left of the window, so we scroll to the left
    // not at the map border
    if (player->x() - CAMERA_LEFT > 0 && player->x() * coef - horizontalScrollBar()->value() < CAMERA_LEFT * coef ){
        horizontalScrollBar()->setValue((player->x() - CAMERA_LEFT) * coef);
        playerInfo->setPos(player->x() - CAMERA_LEFT,playerInfo->y());
        //qDebug() << "left";
    }
    // Player at the begin of the map
    else if (player->x() - CAMERA_LEFT < 0){
        horizontalScrollBar()->setValue(0);
        playerInfo->setPos(0,playerInfo->y());
    }

    // The player is too close to the right of the window, so we scroll to the right
    // not at the map border
    else if (player->x() + WINDOW_WIDTH - CAMERA_RIGHT < map->getWidth() && player->x() * coef - horizontalScrollBar()->value() > CAMERA_RIGHT * coef ){
        //horizontalScrollBar()->setValue(player->x() - CAMERA_RIGHT - offset);
        horizontalScrollBar()->setValue((player->x() - CAMERA_RIGHT)* coef);
        playerInfo->setPos(player->x() - CAMERA_RIGHT ,playerInfo->y());
        //qDebug() << player->x() - CAMERA_RIGHT<< coef <<(player->x() - CAMERA_RIGHT)* coef <<horizontalScrollBar()->value() ;
    }
    /* Player at the end of the map (never happened so commented)
    else if (player->x() + WINDOW_WIDTH - CAMERA_RIGHT > map->getWidth()){
        horizontalScrollBar()->setValue(map->getWidth() - WINDOW_WIDTH - offset);
        playerInfo->setPos(map->getWidth() - WINDOW_WIDTH,playerInfo->y());
    }*/

    //qDebug() << offset <<  player->x() << horizontalScrollBar()->value() << player->x() - horizontalScrollBar()->value() - offset;

}

void GameEngine::updatePositions()
{
    updatePlayerPosition();
    updateCamera();
}

void GameEngine::animate()
{
    // if player in the air
    if(player->isJumping()){
        player->setSprite(QString(":/ressources/images/player/21.png"));
    }
    else if (player->isFalling()){
        player->setSprite(QString(":/ressources/images/player/22.png"));
    }
    // if player run
    else if(player->isMovingRight() || player->isMovingLeft()){
        if(playerSprite < 11 || playerSprite > 13)
            playerSprite = 11;
        player->setSprite(QString(":/ressources/images/player/%1.png").arg(playerSprite));
        playerSprite ++;
    }
    // if player is static
    else if(player->getFixed()){
        if(playerSprite > 4)
            playerSprite = 1;
        player->setSprite(QString(":/ressources/images/player/%1.png").arg(playerSprite));

        playerSprite ++;
        playerStaticCounter ++;
        // if player wink, skip the first sprite
        if(playerSprite == 5){
            playerSprite = 2;
        }
        // if the player do not wink for a while : he will wink
        else if(playerSprite > 3 && playerStaticCounter > 10){
             playerSprite = 4;
             playerStaticCounter = 1;
        }
        // player not wink
        else if(playerSprite > 3 ){
            playerSprite = 1;
        }
    }
    //qDebug() << player->getXForce() << player->getYForce() << player->getFixed();

}

Player *GameEngine::getPlayer() const
{
    return player;
}

void GameEngine::drawElements()
{
    // set scene background
    // setBackgroundBrush(QImage(map->getBackground()));
    this->setBackgroundBrush(QImage(map->getBackground()));


    // set player
    player = map->getPlayer();
    scene->addItem(player);

    // set elements
    for(Element * element : map->getElementList()){
        scene->addItem(element);
    }

    // set mobs
    for(Unit * unit : map->getUnitList()){
        scene->addItem(unit);
    }
}

// FOR TESTS
void createVirus(QGraphicsScene* scene){
    Virus * virus = new Virus();
    virus->setPos(700,450);
    scene->addItem(virus);
}


#include "gameEngine.h"



// for test only

GameEngine::GameEngine()
{
    windowWidth = WINDOW_WIDTH;
    windowHeight = WINDOW_HEIGHT;
    // create the scene
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,MAP_WIDTH,MAP_HEIGHT);
    setScene(gameScene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    //resize(windowWidth,windowHeight);
    showFullScreen();

    // Game plan
    worldPlan = new QGraphicsItemGroup();
    gameScene->addItem(worldPlan);
    // Info plan
    playerInfo = new Info();
    gameScene->addItem(playerInfo);

    map = new Map();
    map->generateMap1();
    drawElements();
    map->saveMap("world 2");
    map->readmap("world 2");
    drawElements();

    menuScene = new Menu;

    // Init Timer
    refreshTimer = new QTimer(this);
    connect(refreshTimer,SIGNAL(timeout()),this,SLOT(updatePositions()));
    Animtimer = new QTimer(this);
    connect(Animtimer,SIGNAL(timeout()),this,SLOT(animate()));

    //show();
    horizontalScrollBar()->setValue(0);
    verticalScrollBar()->setValue(0);
    //horizontalScrollBar()->setMinimum(0);
    //horizontalScrollBar()->setMaximum(map->getWidth() + WINDOW_WIDTH);
    horizontalScrollBar()->setPageStep(0);
    playerSprite = 1;
    playerStaticCounter = 1;

    // Link button menu
    mapper = new QSignalMapper(this);
    foreach(MenuButton * btn ,menuScene->getButtonList()){
        QString worldName = btn->text();
        mapper->setMapping(btn, btn->text());
        connect(btn,SIGNAL(clicked()),mapper,SLOT(map()));
    }
    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(loadMap(QString)));


    openMenu();
    //openGame();

}

GameEngine::~GameEngine()
{
    qDebug() << "delete";
    gameScene->clear();
    delete player;
    delete gameScene;


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
        createVirus();
    }
    else if (event->key() == Qt::Key_Escape){
        map->clearMap();
        openMenu();
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
                map->getUnitList()->removeOne(iterator.key());
                qDebug() << "desl" << map->getUnitList()->count();
                worldPlan->removeFromGroup(iterator.key());
                delete iterator.key();

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

// Follow the player
void GameEngine::updateCamera()
{
    // Player too much to the left
    if (player->x() - CAMERA_LEFT > 0 && player->x() + worldPlan->x() < CAMERA_LEFT ){
        worldPlan->setPos(-(player->x() - CAMERA_LEFT),0);
    }
    // Player at the begin of the map
    else if (player->x() - CAMERA_LEFT < 0){
        worldPlan->setPos(0,0);
    }
    // Player too much to the right
    if (player->x() + WINDOW_WIDTH - CAMERA_RIGHT < map->getWidth() && player->x() + worldPlan->x() > CAMERA_RIGHT ){
        worldPlan->setPos(-(player->x() - CAMERA_RIGHT) , 0);
    }

    /*
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
    //qDebug() << map->getUnitList()->count();
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

void GameEngine::loadMap(QString worldName)
{
    //qDebug() << "loading " << worldName;
    map->readmap(worldName);
    drawElements();
    openGame();
}

Player *GameEngine::getPlayer() const
{
    return player;
}

void GameEngine::drawElements()
{
    // set scene background
    // setBackgroundBrush(QImage(map->getBackground()));
    gameScene->setBackgroundBrush(QImage(map->getBackground()));


    // set player
    player = map->getPlayer();
    //scene->addItem(player);
    worldPlan->addToGroup(player);

    // set elements
    for(Element * element : *map->getElementList()){
        //scene->addItem(element);
        worldPlan->addToGroup(element);
    }

    // set mobs
    for(Unit * unit : *map->getUnitList()){
        //scene->addItem(unit);
        worldPlan->addToGroup(unit);
    }

}

// FOR TESTS
void GameEngine::createVirus(){
    Virus * virus = new Virus();
    worldPlan->addToGroup(virus);
    map->getUnitList()->append(virus);
    virus->setPos(700,450);
}

void GameEngine::openMenu()
{
    Animtimer->stop();
    refreshTimer->stop();
    setScene(menuScene);
}

void GameEngine::openGame()
{
    Animtimer->start(90);
    refreshTimer->start(1000/FPS);
    setScene(gameScene);
}


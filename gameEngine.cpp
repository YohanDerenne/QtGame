#include "gameEngine.h"


GameEngine::GameEngine()
{
    // init sizes
    windowWidth = WINDOW_WIDTH;
    windowHeight = WINDOW_HEIGHT;

    //title and icon
    setWindowTitle(TITLE);
    setWindowIcon(QIcon(":/ressources/images/icone.ico"));

    // create the scene
    levelScene = new QGraphicsScene();
    levelScene->setSceneRect(0,0,MAP_WIDTH,MAP_HEIGHT);
    setScene(levelScene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    //resize(windowWidth,windowHeight);
    //showFullScreen();

    // Game plan
    worldPlan = new QGraphicsItemGroup();
    levelScene->addItem(worldPlan);

    // Info plan
    playerInfo = new Info();
    levelScene->addItem(playerInfo);

    // init map
    map = new Map();
    // Save genarated map
    map->generateMap1();
    map->saveMap("world 2");


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

    // init sprite number for animation
    playerSprite = 1;
    playerStaticCounter = 1;


    // init menu
    menuScene = new Menu();
    // Link level button in menu
    buttonMenuMapper = new QSignalMapper(this);
    foreach(MenuButton * btn ,menuScene->getButtonList()){
        QString worldName = btn->text();
        buttonMenuMapper->setMapping(btn, btn->text());
        connect(btn,SIGNAL(clicked()),buttonMenuMapper,SLOT(map()));
    }
    connect(buttonMenuMapper, SIGNAL(mapped(QString)), this, SLOT(loadMap(QString)));
    // link quit button in menu
    connect(menuScene->getQuitBtn(),SIGNAL(clicked()),this,SLOT(quitApp()));


    // init pause
    pauseMenu = new PauseGroup();
    connect(pauseMenu->getContinueBtn(), SIGNAL(clicked()), this, SLOT(closePause()));
    connect(pauseMenu->getBackMenuBtn(), SIGNAL(clicked()), this, SLOT(openMenu()));

    openMenu();
    //openGame();

}

GameEngine::~GameEngine()
{
    qDebug() << "delete";
    Animtimer->stop();
    delete Animtimer;
    refreshTimer->stop();
    delete refreshTimer;

    delete buttonMenuMapper;

    delete map;
    delete playerInfo;

    delete menuScene;

    delete pauseMenu;

    levelScene->clear();
    delete levelScene;
}

void GameEngine::keyPressEvent(QKeyEvent *event)
{
    //Player control
    if(paused == false){

        if (event->key() == Qt::Key_Left){
            //horizontalScrollBar()->setValue(horizontalScrollBar()->value() - 10);
            map->getPlayer()->SetMovingLeft(true);
        }
        else if (event->key() == Qt::Key_Right){
            //horizontalScrollBar()->setValue(horizontalScrollBar()->value() + 10);
            map->getPlayer()->SetMovingRight(true);
        }
        else if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Up){
            map->getPlayer()->Jump();
        }
        else if (event->key() == Qt::Key_R){
            respawn();
        }
        else if (event->key() == Qt::Key_A){
            createVirus();
        }
    }
    // pause control
    if (event->key() == Qt::Key_Escape){
        if(scene() == levelScene){
            if(pauseMenu->scene() == levelScene)
                closePause();
            else
                openPause();
        }
        //openMenu();
    }
    // full screen control
    if (event->key() == Qt::Key_F11){
        if(isFullScreen())
            showNormal();
        else
            showFullScreen();
    }
}

void GameEngine::keyReleaseEvent(QKeyEvent *event)
{
    //qDebug() << "key released" ;
    if (event->key() == Qt::Key_Left){
        map->getPlayer()->SetMovingLeft(false);
    }
    else if (event->key() == Qt::Key_Right){
        map->getPlayer()->SetMovingRight(false);
    }
}

void GameEngine::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resize";

    // Scale the view to the new size
    QRect rect = QRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    fitInView(rect);
}

void GameEngine::updatePlayerPosition()
{
    map->getPlayer()->updateMovementStates();

    CollideManager<FixedBlock> * wallCollider = new CollideManager<FixedBlock>(map->getPlayer(),true,true,true,true);
    CollideManager<Virus> * virusCollider = new CollideManager<Virus>(map->getPlayer(),true,false,false,false);

    int next_x = map->getPlayer()->x();
    int next_y = map->getPlayer()->y();

    // Moving the player
    if(map->getPlayer()->isFlying() == true){
        next_y += map->getPlayer()->getYForce() * 1/FPS;
        float dt = 1/(float)FPS;
        map->getPlayer()->setYForce( map->getPlayer()->getYForce() + map->getPlayer()->getWeight() * GRAVITY * dt);
    }
    if(map->getPlayer()->isMovingLeft()){
        map->getPlayer()->increaseLeftForce();
    }
    else if(map->getPlayer()->isMovingRight()){
        map->getPlayer()->increaseRightForce();
    }
    else {
        map->getPlayer()->decreaseXForce();
    }
    next_x += map->getPlayer()->getXForce();
    map->getPlayer()->setPos(next_x,next_y);

    wallCollider->updateCollidingPosition();
    virusCollider->updateCollidingPosition();

    // If no collides -> begin de falling
    if(!wallCollider->getAreColliding() &&
            !virusCollider->getAreColliding()){
        if(map->getPlayer()->getYForce() == 0)
            map->getPlayer()->setYForce(map->getPlayer()->getYForce() + 100);
        //player->setXForce(10);
    }
    if(virusCollider->getAreColliding()){
        QMap<Virus *,fromPosition> virusInfo = virusCollider->getCollidingItemList();
        QMapIterator<Virus*, fromPosition> iterator(virusInfo);
        while (iterator.hasNext()) {
            iterator.next();
            if(iterator.value().fromTop == true){
                // rebondi
                map->getPlayer()->setYForce(-200);

                // Kill virus
                map->getUnitList()->removeOne(iterator.key());
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
    map->getPlayer()->setPos(200,400);
}

// Follow the player
void GameEngine::updateCamera()
{
    // Player too much to the left
    if (map->getPlayer()->x() - CAMERA_LEFT > 0 && map->getPlayer()->x() + worldPlan->x() < CAMERA_LEFT ){
        worldPlan->setPos(-(map->getPlayer()->x() - CAMERA_LEFT),0);
    }
    // Player at the begin of the map
    else if (map->getPlayer()->x() - CAMERA_LEFT < 0){
        worldPlan->setPos(0,0);
    }
    // Player too much to the right
    if (map->getPlayer()->x() + WINDOW_WIDTH - CAMERA_RIGHT < map->getWidth() && map->getPlayer()->x() + worldPlan->x() > CAMERA_RIGHT ){
        worldPlan->setPos(-(map->getPlayer()->x() - CAMERA_RIGHT) , 0);
    }
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
    if(map->getPlayer()->isJumping()){
        map->getPlayer()->setSprite(QString(":/ressources/images/player/21.png"));
    }
    else if (map->getPlayer()->isFalling()){
        map->getPlayer()->setSprite(QString(":/ressources/images/player/22.png"));
    }
    // if player run
    else if(map->getPlayer()->isMovingRight() || map->getPlayer()->isMovingLeft()){
        if(playerSprite < 11 || playerSprite > 13)
            playerSprite = 11;
        map->getPlayer()->setSprite(QString(":/ressources/images/player/%1.png").arg(playerSprite));
        playerSprite ++;
    }
    // if player is static
    else if(map->getPlayer()->getFixed()){
        if(playerSprite > 4)
            playerSprite = 1;
        map->getPlayer()->setSprite(QString(":/ressources/images/player/%1.png").arg(playerSprite));

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
    clearLevel();
    map->readmap(worldName);
    drawElements();
    openGame();
}

void GameEngine::drawElements()
{
    // set scene background
    // setBackgroundBrush(QImage(map->getBackground()));
    levelScene->setBackgroundBrush(QImage(map->getBackground()));


    // Add p
    worldPlan->addToGroup(map->getPlayer());

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

    // set bonus
    for(consoObject * conso : *map->getConsoObjectList()){
        //scene->addItem(unit);
        worldPlan->addToGroup(conso);
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
    if(paused == true)
        closePause();

    paused = true;
    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    // stop timers
    Animtimer->stop();
    refreshTimer->stop();

    // replace scene by menu scene
    setScene(menuScene);
}

void GameEngine::quitApp()
{
    this->close();
}

void GameEngine::openGame()
{
    // hide mouse cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // start timer
    Animtimer->start(90);
    refreshTimer->start(1000/FPS);
    setScene(levelScene);
    paused = false;
}

void GameEngine::openPause()
{
    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    // stop timer
    paused = true;
    Animtimer->stop();
    refreshTimer->stop();

    levelScene->addItem(pauseMenu);
    levelScene->addWidget(pauseMenu->getContinueBtn());
    levelScene->addWidget(pauseMenu->getBackMenuBtn());
}

void GameEngine::closePause()
{
    // hide mouse cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // restart timers
    paused = false;
    Animtimer->start(90);
    refreshTimer->start(1000/FPS);

    // remove pause component from scene
    levelScene->removeItem(pauseMenu);
    levelScene->removeItem(pauseMenu->getBackMenuBtn()->graphicsProxyWidget());
    levelScene->removeItem(pauseMenu->getContinueBtn()->graphicsProxyWidget());
    // reset proxy
    pauseMenu->getBackMenuBtn()->graphicsProxyWidget()->setWidget( NULL );
    pauseMenu->getContinueBtn()->graphicsProxyWidget()->setWidget( NULL );
}

void GameEngine::clearLevel()
{
    map->clearMap();
    worldPlan->setPos(0,0);
}


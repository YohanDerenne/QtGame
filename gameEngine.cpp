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
    //setScene(levelScene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    //resize(windowWidth,windowHeight);
    //showFullScreen();

    // Game plan
    worldPlan = new QGraphicsItemGroup();
    levelScene->addItem(worldPlan);


    // init map
    map = new Map();

    // SAVE GENERATED MAP ===================================================
    map->generateMap1();
    map->saveMap("world 2");
    // ======================================================================


    // Init Timer
    refreshTimer = new QTimer(this);
    connect(refreshTimer,SIGNAL(timeout()),this,SLOT(updateAllPositions()));

    Animtimer = new QTimer(this);
    connect(Animtimer,SIGNAL(timeout()),this,SLOT(animate()));
    animFireDuration = 2;

    restartTimer = new QTimer();
    connect(restartTimer,SIGNAL(timeout()),this,SLOT(restart()));

    //show();
    horizontalScrollBar()->setValue(0);
    verticalScrollBar()->setValue(0);
    //horizontalScrollBar()->setMinimum(0);
    //horizontalScrollBar()->setMaximum(map->getWidth() + WINDOW_WIDTH);
    horizontalScrollBar()->setPageStep(0);
    spacePressed = false;

    // init sprite number for animation
    playerSprite = 1;
    playerStaticCounter = 1;

    // init main menu
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

    // init pause menu
    pauseMenu = new PauseGroup();
    connect(pauseMenu->getContinueBtn(), SIGNAL(clicked()), this, SLOT(closePause()));
    connect(pauseMenu->getBackMenuBtn(), SIGNAL(clicked()), this, SLOT(openMenu()));

    // init victory menu
    victoryMenu = new VictoryGroup();
    connect(victoryMenu->getRetryBtn(), SIGNAL(clicked()), this, SLOT(retryMap()));
    connect(victoryMenu->getBackMenuBtn(), SIGNAL(clicked()), this, SLOT(openMenu()));
    finished = false;

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
        else if (event->key() == Qt::Key_Up){
            map->getPlayer()->jump();
        }
        else if (event->key() == Qt::Key_Space){
            // change sprite
            if(spacePressed == false){
                GelProjectile * proj = map->getPlayer()->launchGel(worldPlan->x(), worldPlan->y());
                if(proj != NULL){
                    spacePressed = true;
                    levelScene->addItem(proj);
                    map->getProjectileList()->append(proj);
                }
            }
        }
        else if (event->key() == Qt::Key_R){
            loadMap(map->getName());
        }
        else if (event->key() == Qt::Key_A){
            createVirus();
        }
    }
    // pause control
    if (event->key() == Qt::Key_Escape){
        if(scene() == levelScene && finished == false){
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
    else if (event->key() == Qt::Key_Space){
        if(event->isAutoRepeat())
            event->ignore();
        else
            spacePressed = false;
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
    CollideManager<consoObject> * consoCollider = new CollideManager<consoObject>(map->getPlayer(),false,false,false,false);
    CollideManager<FinishFlag> * flagCollider = new CollideManager<FinishFlag>(map->getPlayer(),false,false,false,false);

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

    // check if out of the map
    if(map->getPlayer()->x() < worldPlan->x() ||
            map->getPlayer()->x() + map->getPlayer()->getWidth() > map->getWidth() ||
            //map->getPlayer()->y() < worldPlan->y() ||
            map->getPlayer()->y() + map->getPlayer()->getWidth() > map->getHeight()){
        gameOver();
    }

    wallCollider->updateCollidingPosition();
    virusCollider->updateCollidingPosition();
    consoCollider->updateCollidingPosition();
    flagCollider->updateCollidingPosition();

    // If no wall or virus collides -> begin de falling
    if(!wallCollider->getAreColliding() &&
            !virusCollider->getAreColliding()){
        // if initial falling
        if(map->getPlayer()->getYForce() == 0)
            map->getPlayer()->setYForce(map->getPlayer()->getYForce() + 100);
    }
    if(virusCollider->getAreColliding()){
        QMap<Virus *,fromPosition> virusMap = virusCollider->getCollidingItemList();
        QMapIterator<Virus*, fromPosition> iterator(virusMap);
        while (iterator.hasNext()) {
            iterator.next();
            Virus * virus = iterator.key();
            if(iterator.value().fromTop == true){
                // rebondi
                map->getPlayer()->bounce();

                // Kill virus
                map->getUnitList()->removeOne(virus);
                worldPlan->removeFromGroup(virus);
                delete iterator.key();
            }
            else{
                // is attacked !
                virus->attack(map->getPlayer());

                // if player is not alive
                if(!map->getPlayer()->isAlive()){
                    gameOver();
                }
            }
        }
    }
    // get conso
    if(consoCollider->getAreColliding()){
        QMap<consoObject *,fromPosition> consoMap = consoCollider->getCollidingItemList();
        QMapIterator<consoObject*, fromPosition> iterator(consoMap);
        while (iterator.hasNext()) {
            iterator.next();
            consoObject * conso = iterator.key();
            conso->applyEffect(map->getPlayer());
            map->getConsoObjectList()->removeOne(conso);
            delete conso;
        }
    }

    // touch the flag
    if(flagCollider->getAreColliding()){
        victory();
    }


    delete wallCollider;
    delete virusCollider;
    delete consoCollider;
    delete flagCollider;
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

void GameEngine::updateAllPositions()
{
    updatePlayerPosition();
    updateProjectilePosition();
    updateCamera();
}

void GameEngine::animate()
{
    // if player immune (get a an attack)
    if(map->getPlayer()->getImmune() && playerSprite % 3 == 0){
        map->getPlayer()->hide();
    }
    else{
        map->getPlayer()->show();
    }

    // attack
    if(spacePressed || playerSprite < 0){
        if(playerSprite > 0){
            playerSprite = -1;
            map->getPlayer()->setSprite(":/ressources/images/player/fire.png");
        }
        else{
            if( - playerSprite < animFireDuration){
                playerSprite --;
            }
            else{
                map->getPlayer()->setFire(false);
                playerSprite = 1;
            }
        }
        return;
    }


    // if player in the air
    else if(map->getPlayer()->isJumping()){
        map->getPlayer()->setSprite(QString(":/ressources/images/player/21.png"));
        playerSprite ++;
    }
    else if (map->getPlayer()->isFalling()){
        map->getPlayer()->setSprite(QString(":/ressources/images/player/22.png"));
        playerSprite ++;
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
        if(playerSprite > 4 || playerSprite < 1)
            playerSprite = 1;
        map->getPlayer()->setSprite(QString(":/ressources/images/player/%1.png").arg(playerSprite));

        playerStaticCounter ++;
        playerSprite ++;
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

void GameEngine::retryMap()
{
    loadMap(map->getName());
}

void GameEngine::loadMap(QString worldName)
{
    levelScene->setSceneRect(0,0,map->getWidth(),map->getHeight());

    if(finished == true){
        closeVictory();
    }

    //qDebug() << "loading " << worldName;
    worldPlan->setPos(0,0);
    clearLevel();
    map->readmap(worldName);
    drawElements();
    openGame();
    //playerInfo->setPos(10,10);
}

void GameEngine::drawElements()
{
    // set scene background
    // setBackgroundBrush(QImage(map->getBackground()));
    levelScene->setBackgroundBrush(QImage(map->getBackground()));


    // Add player
    worldPlan->addToGroup(map->getPlayer());
    map->getPlayer()->setLife(1);


    // Info plan
    levelScene->addItem(map->getPlayerInfo());

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

void GameEngine::updateProjectilePosition()
{
    for(Projectile * projectile : *map->getProjectileList()){
        projectile->move();
        if(projectile->isMaxDist()){
            map->getProjectileList()->removeOne(projectile);
            delete projectile;
            continue;
        }
        QList<QGraphicsItem *> targets = projectile->collidingItems();
        for(QGraphicsItem * target : targets){
            Virus * virus = NULL;
            virus = dynamic_cast<Virus*>(target);
            if(virus){
                projectile->touch(virus);
                if(virus->getLife() == 0 ){
                    map->getUnitList()->removeOne(virus);
                    delete virus;
                    map->getProjectileList()->removeOne(projectile);
                    delete projectile;
                    break;
                }
            }
            FixedBlock * fBlock = NULL;
            fBlock = dynamic_cast<FixedBlock*>(target);
            if(fBlock){
                map->getProjectileList()->removeOne(projectile);
                delete projectile;
                break;
            }
        }
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

void GameEngine::restart()
{
    restartTimer->stop();
    loadMap("world 2");
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
    pauseTimer();

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
    resumeTimer();

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
    if (restartTimer->isActive()){
        restartTimer->stop();
    }
}

void GameEngine::gameOver()
{
    map->getPlayer()->setSprite(":/ressources/images/player/hurt.png");

    pauseTimer();


    restartTimer->start(1000);


}

void GameEngine::pauseTimer()
{
    Animtimer->stop();
    refreshTimer->stop();
    if (restartTimer->isActive() && paused == true){
        overRemainTime = restartTimer->remainingTime();
        restartTimer->stop();
    }
    else
        overRemainTime = 1000;
    if(map->getPlayer()->getGotMask()){
        maskRemainTime = map->getPlayer()->getMaskTimer()->remainingTime();
        map->getPlayer()->getMaskTimer()->stop();
    }
    if(map->getPlayer()->getGotGel()){
        gelRemainTime = map->getPlayer()->getGelTimer()->remainingTime();
        map->getPlayer()->getGelTimer()->stop();
    }
    if(map->getPlayer()->getImmune() && !map->getPlayer()->getGotMask()){
        immuneRemainTime = map->getPlayer()->getImmuneTimer()->remainingTime();
        map->getPlayer()->getImmuneTimer()->stop();
    }

}

void GameEngine::resumeTimer()
{
    if(overRemainTime < 1000)
        restartTimer->start(overRemainTime);
    Animtimer->start(90);
    refreshTimer->start(1000/FPS);

    if(map->getPlayer()->getGotMask()){
        map->getPlayer()->getMaskTimer()->start(maskRemainTime);
    }
    if(map->getPlayer()->getGotGel()){
        map->getPlayer()->getGelTimer()->start(gelRemainTime);
    }
    if(map->getPlayer()->getImmune() && !map->getPlayer()->getGotMask()){
        map->getPlayer()->getImmuneTimer()->start(immuneRemainTime);
    }
}

void GameEngine::victory()
{
    // Show mouse cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);

    pauseTimer();
    finished = true;
    levelScene->addItem(victoryMenu);
    levelScene->addWidget(victoryMenu->getRetryBtn());
    levelScene->addWidget(victoryMenu->getBackMenuBtn());
}

void GameEngine::closeVictory()
{
    // hide mouse cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);
    levelScene->removeItem(victoryMenu);
    finished = false;
    // remove victory component from scene
    levelScene->removeItem(victoryMenu->getBackMenuBtn()->graphicsProxyWidget());
    levelScene->removeItem(victoryMenu->getRetryBtn()->graphicsProxyWidget());
    // reset proxy
    victoryMenu->getBackMenuBtn()->graphicsProxyWidget()->setWidget( NULL );
    victoryMenu->getRetryBtn()->graphicsProxyWidget()->setWidget( NULL );
}



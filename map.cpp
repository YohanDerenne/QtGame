#include "map.h"
#include "configuration.h"

Map::Map()
{
    // set background
    QPixmap bg = QPixmap(":/ressources/images/background.jpg");
    bg = bg.scaled(WINDOW_WIDTH,WINDOW_HEIGHT,Qt::KeepAspectRatioByExpanding);
    setPixmap(bg);

    // create the player
    player = new PlayerView();
    player->setPos(200,200); // TODO generalize to always be in the middle bottom of screen

    // add the player to the scene
    //scene->addItem(player);
}

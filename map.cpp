#include "map.h"

Map::Map()
{

}

void Map::readExample()
{
    width = MAP_WIDTH;
    height = MAP_HEIGHT;

    // set background
    background = QImage(":/ressources/images/background.jpg");
    background = background.scaledToHeight(height);

    // create the player
    player = new Player();
    player->setPos(200,400);

    // add the player to the scene
    //scene->addItem(player);

    // create map
    // floor
    for(int i = 0; i < 15; i++){
        Wall * bloc = new Wall();
        bloc->setPos(i*bloc->getWidth(),500);
        elementList.append(bloc);
        if(i == 12){
            Virus * virus = new Virus();
            virus->setPos(i*bloc->getWidth(), 500 - virus->getHeight());
            unitList.append(virus);
        }

        if(i == 9){
            life *l = new life();
            l->setPos(i*bloc->getWidth(),500 - l->getHeight());
            consoObjectList.append(l);

        }
    }
    // platform
    for(int i = 0; i < 5; i++){
        if(i != 3){
            Wall * bloc = new Wall();
            bloc->setPos(i*bloc->getWidth() + 200 ,300);
            elementList.append(bloc);
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
            Wall * bloc = new Wall();
            bloc->setPos(0 ,500 - bloc->getHeight() - i * bloc->getHeight());
            elementList.append(bloc);
        }

    }
    // little wall
    for(int i = 3; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(500 ,500 - bloc->getHeight() - i * bloc->getHeight());
        elementList.append(bloc);
    }
}

QList<Element *> Map::getElementList() const
{
    return elementList;
}

Player *Map::getPlayer() const
{
    return player;
}

QImage Map::getBackground() const
{
    return background;
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

QList<Unit *> Map::getUnitList() const
{
    return unitList;
}

QList<consoObject *> Map:: getConsoObjectList() const
{
    return consoObjectList;
}

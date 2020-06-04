#include "map.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QDirIterator>

Map::Map()
{
    playerInfo = NULL;
    player = NULL;
    elementList = new QList<Element*>();
    unitList = new QList<Unit*>();
    consoObjectList = new QList<consoObject *>();
    name = "no level";
    projectileList = new QList<Projectile *>();
}

Map::~Map()
{
    clearMap();
    if(player)
        delete player;
    delete elementList;
    delete unitList;
    delete consoObjectList;
    delete projectileList;
}

void Map::generateMap1()
{
    width = MAP_WIDTH;
    height = MAP_HEIGHT;

    // set background
    backgroundPath = ":/ressources/images/backgrounds/background_1.jpg";
    setBackground(QImage(backgroundPath));

    // create the player
    player = new Player();
    player->setPos(200,400);

    // add the player to the scene
    //scene->addItem(player);

    // create map
    // floor
    for(int i = 0; i < 70; i++){
        Wall * bloc = new Wall();
        bloc->setPos(i*bloc->getWidth(),500);
        elementList->append(bloc);
        if(i == 12){
            Virus * virus = new Virus();
            virus->setPos(i*bloc->getWidth(), 500 - virus->getHeight());
            unitList->append(virus);
        }

        // Consos
        if(i == 9){
            Heart *heart = new Heart();
            heart->setPos(i*bloc->getWidth(),500 - heart->getHeight());
            consoObjectList->append(heart);
        }
        if(i == 2){
            Mask *mask = new Mask();
            mask->setPos(i*bloc->getWidth(),500 - mask->getHeight());
            consoObjectList->append(mask);
        }
        if(i == 5){
            Gel *gel = new Gel();
            gel->setPos(i*bloc->getWidth(),500 - gel->getHeight());
            consoObjectList->append(gel);
        }
        if(i == 69){
            FinishFlag *flag = new FinishFlag();
            flag->setPos(i*bloc->getWidth(),500 - flag->getHeight());
            elementList->append(flag);
        }
    }

    // platform
    for(int i = 0; i < 5; i++){
        if(i != 3){
            Wall * bloc = new Wall();
            bloc->setPos(i*bloc->getWidth() + 200 ,300);
            elementList->append(bloc);
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
            elementList->append(bloc);
        }

    }
    // little wall
    for(int i = 3; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(500 ,500 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
    }
}

void Map::generateMap2()
{

}

void Map::generateMapBen()
{
    width = MAP_WIDTH  * 3;
    height = MAP_HEIGHT;

    // set background
    backgroundPath = ":/ressources/images/backgrounds/background_1.jpg";
    setBackground(QImage(backgroundPath));

    // create the player
    player = new Player();
    player->setPos(200,400);

    // add the player to the scene
    //scene->addItem(player);

    // create map
    // floor
    int  offset = 120;
    // first part
    generateRoad(24,0+offset,5);
    generateWall(6,23+offset,6);
    generateRoad(11,13+offset,12);

    // first jump
    generateU(15,7,0,6+offset,9);
    generateWall(2,10+offset,9);

    // first stair
    generateStairs(6,26+offset,5,true);

    // first U
    generateU(6,2,2,34+offset,10);
    generateItem(34+offset+1,11,new MobileVirus());
    // second L
    generateU(11,0,6,38+offset,5);
    generateRoadVirus(4, 38+offset+3, 6);
    generateRoadVirus(4, 38+offset+3, 7);
    generateRoadVirus(4, 38+offset+3, 8);
    generateItem(38+offset+1,6,new Gel());

    // third L
    generateU(4,10,0,42+offset,9);


    // tricky pass
    generateRoad(2,54+offset,5);
    generateRoad(1,58+offset,11);
    generateRoad(30,60+offset,5);



    FinishFlag *flag = new FinishFlag();
   Wall * block = new Wall();
   flag->setPos((offset+85)*block->getWidth() , this->getHeight() - block->getHeight()*(6) );
   elementList->append(flag);


    generateRoad(offset/10,0,6);

    generateRoad(offset/10,offset/8,6);
    generateU(offset/10,2,2,offset/4,6);
    generateU(offset/10,2,2,offset/4+offset/10,6);

    generateRoad(offset/5,offset/4,6);
    generateU(offset/5,3,2,offset/4,6);
    generateItem(offset/4+2,7,new MobileVirus());

    generateRoad(offset/5,offset/2,6);
    generateU(offset/5,2,3,offset/2,6);

    generateRoad(offset/3,offset/2 +offset/5+ 4,6);
    generateStairs(8,offset/2 +offset/5+ 4,6,true);
    generateStairs(8,offset/2 +offset/5+ 12,6,false);





}

// little wall
void Map::generateWall(int height, int xPosition, int yPosition){

    for(int i = 0; i < height; i++){
        Wall * bloc = new Wall();
        bloc->setPos(xPosition*bloc->getWidth() , this->getHeight() - bloc->getHeight()*(yPosition + 1) - i * bloc->getHeight());
        elementList->append(bloc);
    }
}

void Map::generateRoad(int length, int xPosition, int yPosition){

    for(int i = 0; i < length; i++){
        Wall * bloc = new Wall();
        bloc->setPos(xPosition*bloc->getWidth() + i*bloc->getWidth()  , this->getHeight() - bloc->getHeight()*(yPosition+1) );
        elementList->append(bloc);
    }
}


void Map::generateItem(int xPosition, int yPosition,Element * obj){
    Wall * bloc = new Wall();
    obj->setPos(xPosition*bloc->getWidth()   , this->getHeight() - bloc->getHeight()*(yPosition+1) );
    elementList->append(obj);
}

void Map::generateRoadVirus(int length, int xPosition, int yPosition){
    for(int i = 0; i < length; i++){
        Virus * bloc = new Virus();
        bloc->setPos(xPosition*bloc->getWidth() + i*bloc->getWidth()  , this->getHeight() - bloc->getHeight()*(yPosition+1) );
        elementList->append(bloc);
    }
}

void Map::generateStairs(int length, int xPosition, int yPosition,bool isLeftEmpty){

    if(isLeftEmpty){
        for(int i = 0; i < length; i++){
            generateRoad(length-i,xPosition+i,yPosition+i);
        }
    }
    else{
        for(int i = 0; i < length; i++){
            generateRoad(length-i,xPosition,yPosition+i);
        }
    }

}

void Map::generateU(int xLength,int yLengthLeft, int yLengthRight, int xPosition, int yPosition){


    generateRoad(xLength,xPosition,yPosition);      // ground
    generateWall(yLengthLeft,xPosition,yPosition+1);// left wall
    generateWall(yLengthRight,xPosition+xLength-1,yPosition+1);// rightWall


}

void Map::generateRectangle(int length,int height, int xPosition,int yPosition){
    for(int i = 0; i<height;i++){
        generateRoad(length,xPosition,yPosition+i);
    }
}
bool Map::readmap(QString directory)
{
    // Clear the actual map if exists
    clearMap();

    name = directory;

    // Open the json file
    QDir dir = directory;
    QString path = QStringLiteral("levels/%1/map.json").arg(directory);
    QFile loadFile(path);
    // qDebug() << path;
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return false;
    }

    // Read data
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    // transform brut data to json data
    QJsonObject mapJson = loadDoc.object();

    // read json elements
    height = mapJson["height"].toInt();
    width = mapJson["width"].toInt();

    backgroundPath = mapJson["background"].toString();
    background = QImage(backgroundPath);
    background = background.scaledToHeight(height);

    QJsonArray elemTab = mapJson["elem"].toArray();
    for (int index = 0; index < elemTab.size(); ++index) {
        QJsonObject elem = elemTab[index].toObject();
        if(elem["type"].toString() == "player"){
            player = new Player();
            player->setX(elem["x"].toInt());
            player->setY(elem["y"].toInt());

            playerInfo = new Info();
            player->setInfo(playerInfo);
        }
        if(elem["type"].toString() == "wall"){
            Wall * w = new Wall();
            w->setX(elem["x"].toInt());
            w->setY(elem["y"].toInt());
            elementList->append(w);
        }
        if(elem["type"].toString() == "virus"){
            Virus * v = new Virus();
            v->setX(elem["x"].toInt());
            v->setY(elem["y"].toInt());
            unitList->append(v);
        }
        if(elem["type"].toString() == "gel"){
            Gel * gel = new Gel();
            gel->setX(elem["x"].toInt());
            gel->setY(elem["y"].toInt());
            consoObjectList->append(gel);
        }
        if(elem["type"].toString() == "heart"){
            Heart * heart = new Heart();
            heart->setX(elem["x"].toInt());
            heart->setY(elem["y"].toInt());
            consoObjectList->append(heart);
        }
        if(elem["type"].toString() == "mask"){
            Mask * mask = new Mask();
            mask->setX(elem["x"].toInt());
            mask->setY(elem["y"].toInt());
            consoObjectList->append(mask);
        }
        if(elem["type"].toString() == "finish"){
            FinishFlag * flag = new FinishFlag();
            flag->setX(elem["x"].toInt());
            flag->setY(elem["y"].toInt());
            elementList->append(flag);
        }
        if(elem["type"].toString() == "mobileVirus"){
            MobileVirus * mbVir = new MobileVirus();
            mbVir->setX(elem["x"].toInt());
            mbVir->setY(elem["y"].toInt());
            unitList->append(mbVir);
        }
    }
    loadFile.close();
    return true;
}

void Map::clearMap()
{
    if(player != NULL){
        //qDebug() << player;
        delete player;
        player = NULL;
    }

    if(playerInfo != NULL){
        delete playerInfo;
        playerInfo = NULL;
    }


    for(Element * elem : *elementList){
        delete elem;
    }
    elementList->clear();

    for(Unit * unit: *unitList){
        delete unit;
    }
    unitList->clear();

    for(Unit * unit: *projectileList){
        delete unit;
    }
    projectileList->clear();

    for(consoObject * conso: *consoObjectList){
        delete conso;
    }
    consoObjectList->clear();
}

bool Map::saveMap(QString directory)
{
    // Open the file
    QDir dir =  QStringLiteral("levels/%1").arg(directory);;
    QString path = QStringLiteral("levels/%1/map.json").arg(directory);
    QFile saveFile(path);
    qDebug() << dir.absolutePath();
    QDir dirLevel = QString("levels");
    // create levels directory if not exists
    if(!dirLevel.exists()){
        QDir().mkdir(QString("levels"));
    }

    // create map directory if not exists
    if(!dir.exists()){
        QDir().mkdir( QStringLiteral("levels/%1").arg(directory));
    }

    // Open file and create it if not exists
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject mapJson;
    QJsonArray jsonTab;

    // Save the map in mapJson
    mapJson["height"] = height;
    mapJson["width"] = width;
    mapJson["background"] = backgroundPath;
    foreach (Element * elem, *elementList) {
        QJsonObject jsonObject;
        jsonObject["type"] = elem->getType();
        jsonObject["x"] = elem->x();
        jsonObject["y"] = elem->y();
        jsonTab.append(jsonObject);
    }
    foreach (Element * elem, *unitList) {
        QJsonObject jsonObject;
        jsonObject["type"] = elem->getType();
        jsonObject["x"] = elem->x();
        jsonObject["y"] = elem->y();
        jsonTab.append(jsonObject);
    }
    foreach (Element * elem, *consoObjectList) {
        QJsonObject jsonObject;
        jsonObject["type"] = elem->getType();
        jsonObject["x"] = elem->x();
        jsonObject["y"] = elem->y();
        jsonTab.append(jsonObject);
    }
    QJsonObject playerJson;
    playerJson["type"] = player->getType();
    playerJson["x"] = player->x();
    playerJson["y"] = player->y();
    jsonTab.append(playerJson);
    mapJson["elem"] = jsonTab;

    // save and write de mapJson
    QJsonDocument saveDoc(mapJson);
    saveFile.write(saveDoc.toJson());

    // success
    saveFile.close();
    return true;
}

QList<Element *> * Map::getElementList() const
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

void Map::setBackground(const QImage &value)
{
    background = value.scaledToHeight(height);
}

QList<QString> Map::getLevels()
{
    QList<QString> list;
    QDirIterator iterator("levels");
    while (iterator.hasNext()) {
        QString dir = iterator.next();
        dir.remove("levels/");
        if(dir != "." && dir != "..")
            list.append(dir);
    }
    return list;
}

QString Map::getName() const
{
    return name;
}

Info *Map::getPlayerInfo() const
{
    return playerInfo;
}

QList<Projectile *> *Map::getProjectileList() const
{
    return projectileList;
}

QList<Unit *> * Map::getUnitList() const
{
    return unitList;
}

QList<consoObject *> * Map:: getConsoObjectList() const
{
    return consoObjectList;
}

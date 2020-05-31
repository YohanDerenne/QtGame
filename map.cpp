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

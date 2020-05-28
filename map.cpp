#include "map.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QDirIterator>

Map::Map()
{
    player = NULL;
    elementList = new QList<Element*>();
    unitList = new QList<Unit*>();
}

Map::~Map()
{
    clearMap();
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
        }

    return true;
}

void Map::clearMap()
{
    if(player != NULL){
        delete player;
        player = NULL;
    }
    for(Element * elem : *elementList){
        delete elem;
    }
    elementList->clear();
    //qDebug() << unitList.count();
    for(Unit * unit: *unitList){
        //qDebug() << unit->getType();
        delete unit;
    }
    unitList->clear();
    //qDebug() << unitList.count();
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
        QJsonObject npcObject;
        npcObject["type"] = elem->getType();
        npcObject["x"] = elem->x();
        npcObject["y"] = elem->y();
        jsonTab.append(npcObject);
    }
    foreach (Element * elem, *unitList) {
        QJsonObject npcObject;
        npcObject["type"] = elem->getType();
        npcObject["x"] = elem->x();
        npcObject["y"] = elem->y();
        jsonTab.append(npcObject);
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

QList<Unit *> * Map::getUnitList()
{
    return unitList;
}

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
    name = "noNamedlevel";
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

    //don't forget qrc for music
    musicPath = "qrc:/ressources/sounds/Castle_of_Funk.mp3";

    // create the player
    player = new Player();
    player->setPos(200,400);

    name = "Paradyze";

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

        // for mobile virus
        if(i==25){
            Wall * bloc2 = new Wall();
            bloc2->setPos(i*bloc->getWidth(),500 - bloc2->getHeight());
            elementList->append(bloc2);
        }
        if(i==23){
            MobileVirus * mb = new MobileVirus();
            mb->setPos(i*bloc->getWidth(),500 - mb->getHeight());
            unitList->append(mb);
        }
        if(i == 19 || i==20){
            // hole
            elementList->removeOne(bloc);
            delete bloc;
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
    width = MAP_WIDTH;
    height = MAP_HEIGHT;

    // set background
    backgroundPath = ":/ressources/images/backgrounds/background_2.png";

    //don't forget qrc for music
    musicPath = "qrc:/ressources/sounds/kirby.mp3";

    // create the player
    player = new Player();
    player->setPos(200,600);

    name = "Paradyze";

    // add the player to the scene
    //scene->addItem(player);

    // create map
    // floor
    for(int i = 0; i < 60; i++){
        if(i != 30 && i != 31){
            Wall * bloc = new Wall();

            bloc->setPos(i*bloc->getWidth(),660);
            elementList->append(bloc);
        }
        Wall * bloc = new Wall();

        if(i == 13){
            Mask *mask = new Mask();
            mask->setPos(i*bloc->getWidth(),510 - mask->getHeight());
            consoObjectList->append(mask);
        }
        if(i == 25){
            Virus * virus = new Virus();
            virus->setPos(i*bloc->getWidth(), 430 - virus->getHeight());
            unitList->append(virus);
        }

        if(i == 34){
            Gel *gel = new Gel();
            gel->setPos(i*bloc->getWidth(),430 - gel->getHeight());
            consoObjectList->append(gel);
        }
        delete bloc;
    }

    for (int i = 37;i<60;i++) {
        if(i != 47 && i != 48){

            Wall * bloc = new Wall();
            bloc->setPos(i*bloc->getWidth(),510);
            elementList->append(bloc);

            //flag
            if(i == 57){
                FinishFlag *flag = new FinishFlag();
                flag->setPos(i*bloc->getWidth(),510 - flag->getHeight());
                elementList->append(flag);
            }
        }
    }
    //End wall
    for(int i = 3; i >= 0; i--){

        Wall * bloc = new Wall();
        bloc->setPos(3000 ,710 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);


    }

    // platform
    for(int i = 5; i < 10; i++){
        if(i != 9){

            Wall * bloc = new Wall();
            bloc->setPos(i*bloc->getWidth() + 900 ,430);
            elementList->append(bloc);
        }

    }

    for(int i = 0; i >= 0; i--){

        Wall * bloc = new Wall();
        bloc->setPos(i*bloc->getWidth() + 1690 ,430);
        elementList->append(bloc);

    }


    // little wall
    for(int i = 1; i >= 0; i--){
        Wall * bloc = new Wall();
        Wall * bloc1 = new Wall();
        bloc->setPos(500 ,660 - bloc->getHeight() - i * bloc->getHeight());
        bloc1->setPos(750 ,660 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
        elementList->append(bloc1);
    }
    // little wall
    for(int i = 2; i >= 0; i--){
        Wall * bloc = new Wall();
        Wall * bloc1 = new Wall();
        Wall * bloc2 = new Wall();
        Wall * bloc3 = new Wall();
        bloc->setPos(550 ,660 - bloc->getHeight() - i * bloc->getHeight());
        bloc1->setPos(600 ,660 - bloc->getHeight() - i * bloc->getHeight());
        bloc2->setPos(650 ,660 - bloc->getHeight() - i * bloc->getHeight());
        bloc2->setPos(650 ,660 - bloc->getHeight() - i * bloc->getHeight());
        bloc3->setPos(700 ,660 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
        elementList->append(bloc1);
        elementList->append(bloc2);
        elementList->append(bloc3);
    }
}


void Map::generateCityWorld()
{
    width = MAP_WIDTH * 2;
    height = MAP_HEIGHT;

    // set background
    backgroundPath = ":/ressources/images/backgrounds/city.jpg";

    //don't forget qrc for music
    musicPath = "qrc:/ressources/sounds/drop_gems.mp3";

    // create the player
    player = new Player();
    player->setPos(200,400);
    //player->setPos(2000,400);

    name = "City NightFall";

    // wall
    for(int i = 15; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(0 ,950 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
    }

    // 1st floor
    for(int i = 0; i < 20; i++){
        Wall * bloc = new Wall();
        bloc->setPos((i+1)*bloc->getWidth(),500);
        elementList->append(bloc);
    }
    // 2nd floor
    for(int i = 0; i < 20; i++){
        Wall * bloc = new Wall();
        bloc->setPos((i+10)*bloc->getWidth(),700);
        elementList->append(bloc);
    }
    // 3rd floor
    for(int i = 0; i < 36; i++){
        if(i!= 2 && i!= 5 && i!= 7 && i!=22 && i!=23){
            Wall * bloc = new Wall();
            bloc->setPos((i+1)*bloc->getWidth(),900);
            elementList->append(bloc);

            // gel
            if(i == 1){
                Gel * gel = new Gel();
                gel->setPos((i+1)*bloc->getWidth(),900 - gel->getHeight());
                consoObjectList->append(gel);
            }

            if(i==3){
                // virus wall
                for(int j = 0 ; j<3 ; j ++){
                    Virus * virus = new Virus();
                    virus->setPos((i+1)*bloc->getWidth(),900 - (j+1) * virus->getHeight());
                    unitList->append(virus);
                }
            }
            if(i==6){
                // virus wall
                for(int j = 0 ; j<3 ; j ++){
                    Virus * virus = new Virus();
                    virus->setPos((i+1)*bloc->getWidth(),900 - (j+1) * virus->getHeight());
                    unitList->append(virus);
                }
            }
            if(i==9){
                // virus wall
                for(int j = 0 ; j<3 ; j ++){
                    Virus * virus = new Virus();
                    virus->setPos((i+1)*bloc->getWidth(),900 - (j+1) * virus->getHeight());
                    unitList->append(virus);
                }
            }
        }
    }

    // 2nd wall
    for(int i = 8; i >= 0; i--){
        Wall * bloc = new Wall();
        bloc->setPos(1500 ,750 - bloc->getHeight() - i * bloc->getHeight());
        elementList->append(bloc);
        if(i == 5){
            Wall * bloc2 = new Wall();
            bloc2->setPos(1500 + bloc->getWidth(),750 - i * bloc2->getHeight());
            elementList->append(bloc2);

            // heart
            Heart * heart = new Heart();
            heart->setPos(1500 + bloc->getWidth(),750 - i * bloc2->getHeight() - heart->getHeight());
            consoObjectList->append(heart);
        }
        if(i==1){
            // wall blocker with virus
            for(int j=0 ; j<6 ; j++){
                Wall * vir = new Wall();
                vir->setPos(1500 + bloc->getWidth() + j*vir->getWidth(),750 - i * bloc->getHeight());
                elementList->append(vir);
            }
            MobileVirus * mbvir = new MobileVirus();
            mbvir->setPos(1500 + bloc->getWidth(),750 - i * bloc->getHeight() - mbvir->getHeight());
            unitList->append(mbvir);
        }
    }

    // 3rd wall
    for(int i = 0 ; i<13 ; i++){
        Wall * bloc = new Wall();
        bloc->setPos(1800 ,50 + i * bloc->getHeight());
        elementList->append(bloc);
        if(i==4){
            // heart
            Heart * heart = new Heart();
            heart->setPos(1800 + bloc->getWidth(),750 - i * bloc->getHeight());
            consoObjectList->append(heart);
        }
    }

    // 4th floor
    for(int i=0 ; i<30 ; i++){
        Wall * bloc = new Wall();
        bloc->setPos(2000 + i*bloc->getWidth() ,900);
        elementList->append(bloc);
        // border
        if(i == 0 || i == 29){
            Wall * bloc2 = new Wall();
            bloc2->setPos(2000 + i*bloc->getWidth() ,900 - bloc->getHeight());
            elementList->append(bloc2);
        }
        // virus mobile
        if(i == 1){
            MobileVirus * mobVir = new MobileVirus();
            mobVir->setPos(2000 + i*bloc->getWidth() ,900 - mobVir->getHeight());
            unitList->append(mobVir);
        }
        // virus mobile
        if(i == 10){
            MobileVirus * mobVir = new MobileVirus();
            mobVir->setPos(2000 + i*bloc->getWidth() ,900 - mobVir->getHeight());
            unitList->append(mobVir);
        }
    }
    // 5th floor
    for(int i=0 ; i<30 ; i++){
        Wall * bloc = new Wall();
        bloc->setPos(3800 + i*bloc->getWidth() ,750);
        elementList->append(bloc);
        // border
        if(i == 0 || i == 29){
            Wall * bloc2 = new Wall();
            bloc2->setPos(3800 + i*bloc->getWidth() ,750 - bloc->getHeight());
            elementList->append(bloc2);
        }
        // 3 virus mobile
        if(i == 1 || i==10 || i==20){
            MobileVirus * mobVir = new MobileVirus();
            mobVir->setPos(3800 + i*bloc->getWidth() ,750 - mobVir->getHeight());
            unitList->append(mobVir);
        }
    }
    // 5th floor
    for(int i=0 ; i<30 ; i++){
        Wall * bloc = new Wall();
        bloc->setPos(5600 + i*bloc->getWidth() ,600);
        elementList->append(bloc);
        // border
        if(i == 0 || i == 29){
            Wall * bloc2 = new Wall();
            bloc2->setPos(5600 + i*bloc->getWidth() ,600 - bloc->getHeight());
            elementList->append(bloc2);
            if(i==29){
                FinishFlag * flag = new FinishFlag();
                flag->setPos(5600 + i*bloc->getWidth() ,600 - bloc->getHeight() - flag->getHeight());
                elementList->append(flag);
            }
            else{
                Heart * heart = new Heart();
                heart->setPos(5600 + i*bloc->getWidth() ,600 - bloc->getHeight() - heart->getHeight());
                elementList->append(heart);
            }
        }
        // 4 virus mobile
        if(i == 1 || i==10 || i==20 || i == 25){
            MobileVirus * mobVir = new MobileVirus();
            mobVir->setPos(5600 + i*bloc->getWidth() ,600 - mobVir->getHeight());
            unitList->append(mobVir);
        }
        // virus wall
        if(i==7 || i == 15 || i== 27){
            for(int j=0; j<3 ; j++){
                Virus * virus = new Virus();
                virus->setPos(5600 + (i+1)*bloc->getWidth(),600 - (j+1) * virus->getHeight());
                unitList->append(virus);
            }
        }
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
    musicPath = mapJson["music"].toString();

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
    mapJson["music"] = musicPath;
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

QString Map::getMusic() const
{
    return musicPath;
}

QList<Unit *> * Map::getUnitList() const
{
    return unitList;
}

QList<consoObject *> * Map:: getConsoObjectList() const
{
    return consoObjectList;
}

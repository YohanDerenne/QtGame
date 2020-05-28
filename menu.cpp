#include "menu.h"

 #include <QStyleHints>
Menu::Menu() : QGraphicsScene()
{
    int xButton = 200;
    int yStartButton = 300;
    int buttonSperator = 50;

    // Create window scene with background
    this->setSceneRect(0,0,MAP_WIDTH,MAP_HEIGHT);
    QImage background = QImage(":/ressources/images/backgrounds/background_menu.png");
    background = background.scaledToHeight(WINDOW_HEIGHT);
    this->setBackgroundBrush(background);

    // Display buttons
    int index = 0;
    foreach (QString world, Map::getLevels() ){
        qDebug() << world;
        MenuButton * button = new MenuButton(world);
        button->move(xButton,yStartButton + index * (button->height() + buttonSperator));
        buttonList.append(button);
        this->addWidget(button);
        index ++;
    }

    // Player Image
    QGraphicsPixmapItem * playerImage = new QGraphicsPixmapItem();
    QPixmap img = QPixmap(":/ressources/images/player/1.png");
    img = img.scaled(400,600);
    playerImage->setPixmap(img);
    playerImage->setPos(1000,400);
    this->addItem(playerImage);

    // Title
    QGraphicsTextItem * title = new QGraphicsTextItem();
    title->setPlainText("Virus Fighter");
    QFont font = QFont("Agency FB",100);
    font.setBold(true);
    title->setFont(font);
    title->setPos(900,200);
    this->addItem(title);



}

#include "menu.h"

 #include <QStyleHints>
Menu::Menu() : QGraphicsScene()
{
    int xButton = 200;
    int yStartButton = 300;
    // Create window scene with background
    this->setSceneRect(0,0,MAP_WIDTH,MAP_HEIGHT);
    QImage background = QImage(":/ressources/images/backgrounds/background_menu.png");
    background = background.scaledToHeight(WINDOW_HEIGHT);
    this->setBackgroundBrush(background);

    // Display levels buttons
    int index = 0;
    foreach (QString world, Map::getLevels() ){
        qDebug() << world;
        MenuButton * button = new MenuButton(world);
        button->move(xButton,yStartButton + index * (button->height() + BTN_GAP));
        buttonList.append(button);
        this->addWidget(button);
        index ++;
    }

    // display quitBtn
    QuitBtn= new MenuButton("Quit");
    QuitBtn->move(xButton,yStartButton + index * (QuitBtn->height() + BTN_GAP));
    this->addWidget(QuitBtn);

    // Player Image
    QGraphicsPixmapItem * playerImage = new QGraphicsPixmapItem();
    QPixmap img = QPixmap(":/ressources/images/player/1.png");
    img = img.scaled(400,600);
    playerImage->setPixmap(img);
    playerImage->setPos(1000,400);
    this->addItem(playerImage);

    // Title
    QGraphicsTextItem * title = new QGraphicsTextItem();
    title->setPlainText(TITLE);
    QFont font = QFont("Agency FB",100);
    font.setBold(true);
    title->setFont(font);
    title->setPos(900,200);
    this->addItem(title);



}

Menu::~Menu()
{
    foreach(QPushButton * btn,buttonList){
        delete btn;
    }
    buttonList.clear();
    delete QuitBtn;
}

QList<MenuButton *> Menu::getButtonList() const
{
    return buttonList;
}

MenuButton *Menu::getQuitBtn() const
{
    return QuitBtn;
}

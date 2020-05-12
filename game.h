#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "element.h"
#include "map.h"


class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    ~Game();

    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void updatePlayerPosition();

public slots:
    void updatePositions();

private:
    QGraphicsScene * scene;
    Player * player;
    QImage background;
    QList<Element *> elementList;
    Map * map;

    int windowWidth;
    int windowHeight;
};


#endif // GAME_H

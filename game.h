#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "playerview.h"

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    ~Game();

    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsScene * scene;
    PlayerView * player;
    QImage background;
    float ratio;

};


#endif // GAME_H

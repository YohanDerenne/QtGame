#include "bloc.h"
#include "configuration.h"

Bloc::Bloc()
{
    QPixmap blocSprite = QPixmap(":/ressources/images/bloc.png");
    blocSprite = blocSprite.scaled(BLOC_SIZE,BLOC_SIZE);
    setPixmap(blocSprite);
}

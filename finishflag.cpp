#include "finishflag.h"

FinishFlag::FinishFlag() : Element()
{
    type = "finish";
    width = FLAG_WIDTH;
    height = FLAG_HEIGHT;

    // set graphic
    setSprite(":/ressources/images/flag.png");
}

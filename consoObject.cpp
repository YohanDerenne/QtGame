#include "consoObject.h"

consoObject::consoObject(){

    durationOfEffect = 0;

}

void consoObject::setDurationOfEffect(int value)
{
    durationOfEffect = value;
}

int consoObject::getDurationOfEffect() const
{
    return durationOfEffect;
}

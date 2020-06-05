#include "mobilevirus.h"

MobileVirus::MobileVirus() : Virus()
{
    type = "mobileVirus";
    isRightSide = true;
    setXForce(10);
}

void MobileVirus::switchSide()
{
    if(isRightSide){
        isRightSide = false;
        setXForce(-10);
    }
    else{
        isRightSide = true;
        setXForce(10);
    }

}

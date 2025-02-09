#include "shootBehaviours.h"

bool AutoShootBehaviour::isAuto() const{
    return true;
}
bool ManualShootBehaviour::isAuto() const{
    return false;
}

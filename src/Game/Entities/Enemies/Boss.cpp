#include "Boss.h"
#include "OverworldCamera.h"

Boss::Boss() :
    EntityFighter(HitBox(0, 0, 50, 64), HitBox(420, 220, 97, 125), 10, 10)
{

}

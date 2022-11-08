#include "Boundry.h"

Boundry::Boundry(int x, int y, int width, int height) 
    : HitBox(x, y, width, height)
{
    setSolid(true);
}

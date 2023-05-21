#include "Hexagon.h"

float distance (const myHexagon* a, const myHexagon* b)
{
    return sqrt(pow(a->getPosition().x - b->getPosition().x, 2) + pow(a->getPosition().y - b->getPosition().y, 2));
}

#include "Hexagon.h"

myHexagon::myHexagon(const sf::Vector2f &position, const sf::Color &color) : sf::CircleShape(HEX_SIZE, 6)
{
    this->setOrigin({HEX_SIZE, HEX_SIZE + 50.0f});
    this->setPosition(position);
    this->setFillColor(color);
    this->setOutlineColor(sf::Color::Yellow);
    this->rotate(sf::degrees(90.0f));
}


float distance (const myHexagon* a, const myHexagon* b)
{
    return sqrt(pow(a->getPosition().x - b->getPosition().x, 2) + pow(a->getPosition().y - b->getPosition().y, 2));
}

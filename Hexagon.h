#pragma once
#include <SFML/Graphics.hpp>

const float HEX_SIZE = 40.0f;
const float HEX_RADIUS = HEX_SIZE * 0.866f;
const sf::Color P1_COLOR = sf::Color::Red;
const sf::Color P2_COLOR = sf::Color::Blue;

enum Player
{
    Player1,
    Player2
};

class myHexagon : public sf::CircleShape
{
private:
    sf::Vector2f position;
    sf::Color color;
    Player player = Player::Player1;
public:
    // extends the constructor of sf::CircleShape
    myHexagon(const sf::Vector2f &position, const sf::Color &color) : sf::CircleShape(HEX_SIZE, 6)
    {
        this->setOrigin(HEX_SIZE, HEX_SIZE + 50.0f);
        this->setPosition(position);
        this->setFillColor(color);
        this->setOutlineColor(sf::Color (255 , 255 , 0));
        this->rotate(90.0f);
    }
};


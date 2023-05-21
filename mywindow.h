#pragma once
#include <SFML/Graphics.hpp>

const int BOARD_SIZE = 9;
const float HEX_SIZE = 40.0f;
const float HEX_RADIUS = HEX_SIZE * 0.866f;
const float HEX_VERTICAL_SPACING = HEX_SIZE * 2.0f;
const float HEX_HORIZONTAL_SPACING = HEX_RADIUS * 2.0f;

class myWindow : public sf::RenderWindow
{
public:
    using sf::RenderWindow::RenderWindow;
    // destructor
    ~myWindow()
    {
        for (auto hex : hexagons)
        {
            delete hex;
        }
    }
    std::vector<sf::CircleShape*> hexagons;
    void addHexagon(sf::CircleShape* hex)
    {
        hexagons.push_back(hex);
        drawHexagon(*this, hex->getPosition(), hex->getFillColor());
    }
    void drawHexagon(sf::RenderWindow &window, sf::Vector2f position, sf::Color fillColor)
    {
        sf::CircleShape hexagon = sf::CircleShape(HEX_SIZE, 6);
        hexagon.setOrigin(HEX_SIZE, HEX_SIZE + 50.0f);
        hexagon.setPosition(position);
        hexagon.setFillColor(fillColor);
        hexagon.rotate(90.0f);
        window.draw(hexagon);
    }
};

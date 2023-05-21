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
    std::vector<sf::CircleShape *> hexagons{};
    using sf::RenderWindow::RenderWindow;
    // destructor
    ~myWindow()
    {
        for (auto hex : hexagons)
        {
            delete hex;
        }
    }
    void innitBoard()
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (((i == 0 || i == BOARD_SIZE - 1) && (j == 0 || j == 1 || j == BOARD_SIZE - 1 || j == BOARD_SIZE - 2)) || ((i == 1 || i == BOARD_SIZE - 2) && (j == 0 || j == BOARD_SIZE - 1 || j == BOARD_SIZE - 2)) || ((i == 2 || i == BOARD_SIZE - 3) && (j == 0 || j == BOARD_SIZE - 1)) || ((i == 3 || i == BOARD_SIZE - 4) && (j == BOARD_SIZE - 1)) || (i == 4 && j == 3) || ((i == 3 || i == 5) && j == 4))
                    continue;

                float x = HEX_HORIZONTAL_SPACING * (i + 1);
                float y = HEX_VERTICAL_SPACING * (j + 1);
                if (i % 2 != 0)
                {
                    y += HEX_VERTICAL_SPACING / 2.0f;
                }
                sf::CircleShape *hexagon = new sf::CircleShape(HEX_SIZE, 6);
                hexagon->setOrigin(HEX_SIZE, HEX_SIZE + 50.0f);
                hexagon->setPosition(sf::Vector2f(x, y));
                hexagon->setFillColor(sf::Color::Red);
                hexagon->rotate(90.0f);
                draw(*hexagon);
                hexagons.push_back(hexagon);
            }
        }
    }
    void redrawBoard()
    {
        for (auto hex : hexagons)
        {
            draw(*hex);
        }
    }
};

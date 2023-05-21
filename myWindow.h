#pragma once
#include <SFML/Graphics.hpp>
#include "Hexagon.h"

const int BOARD_SIZE = 9;

const float HEX_VERTICAL_SPACING = HEX_SIZE * 2.0f;
const float HEX_HORIZONTAL_SPACING = HEX_RADIUS * 2.0f;


class myWindow : public sf::RenderWindow
{
myHexagon *selectedHexagon = nullptr;
public:
    Player player = Player::Player1;
    std::vector<myHexagon *> hexagons{};
    using sf::RenderWindow::RenderWindow;
    // destructor
    ~myWindow()
    {
        for (auto hex : hexagons)
        {
            delete hex;
        }
        if (selectedHexagon != nullptr)
        {
            delete selectedHexagon;
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
                // myHexagon *hexagon = new myHexagon(HEX_SIZE, 6);
                // hexagon->setOrigin(HEX_SIZE, HEX_SIZE + 50.0f);
                // hexagon->setPosition(sf::Vector2f(x, y));
                // hexagon->setFillColor(sf::Color::White);
                // hexagon->setOutlineColor(sf::Color (255 , 255 , 0));
                // hexagon->rotate(90.0f);
                myHexagon *hexagon = new myHexagon(sf::Vector2f(x, y), sf::Color::White);
                if ((i == 4 && j == 0) || (i == 0 && j == 6) || (i == BOARD_SIZE - 1 && j == 6))
                {
                    hexagon->setFillColor(sf::Color::Red);
                }
                else if ((i == 4 && j == 8) || (i == 0 && j == 2) || (i == BOARD_SIZE - 1 && j == 2))
                {
                    hexagon->setFillColor(sf::Color::Blue);
                }
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

    void selectHexagon(myHexagon *hexagon)
    {
        for (auto hex : hexagons)
        {
            hex->setOutlineThickness(0);
        }

        // check if a hexagon is already selected
        if (selectedHexagon != nullptr)
        {
            // check if the color of hexagon is white
            if (hexagon->getFillColor() == sf::Color::White)
            {
                // set the color of the hexagon to the color of the selected hexagon
                hexagon->setFillColor(selectedHexagon->getFillColor());
                // set the color of the selected hexagon to white
                selectedHexagon->setFillColor(sf::Color::White);
                // change the player
                player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
            }
        }
        
        selectedHexagon = nullptr;
        // if the player matches the color of the hexagon
        // create an outline around the hexagon
        if ((hexagon->getFillColor() == P1_COLOR and player == Player::Player1) ||
            (hexagon->getFillColor() == P2_COLOR and player == Player::Player2))
        {
            selectedHexagon = hexagon;
            hexagon->setOutlineThickness(5);
        }
    }

    myHexagon *getSelectedHexagon() const
    {
        return selectedHexagon;
    }


};

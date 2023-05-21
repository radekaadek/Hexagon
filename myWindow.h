#pragma once
#include <SFML/Graphics.hpp>
#include "Hexagon.h"
#include <cmath>
#include <iostream>

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

    std::vector<myHexagon*> getNeighbours(myHexagon* center)
    {
        std::vector<myHexagon*> neighbours = {};
        for (auto hex : hexagons)
        {
            if (hex == center)
            {
                continue;
            }
            // check distance between center and hex
            if (distance(center,hex) < HEX_SIZE * 2.2f)
            {
                neighbours.push_back(hex);
            }
        }
        return neighbours;
    }


    void moveHexagon(myHexagon *start, myHexagon *end) {
        // swap the colors of the hexagons
        sf::Color temp = start->getFillColor();
        if (distance(start, end) > HEX_SIZE * 2.2f)
            start->setFillColor(end->getFillColor());
        end->setFillColor(temp);
        // check if nearby hexagons are the opposite color
        // if they are, change their color to the color of the player
        std::vector<myHexagon*> neighbours = getNeighbours(end);
        for (auto hex : neighbours)
        {
            if(hex->getFillColor() == P1_COLOR && player == Player::Player2)
            {
                hex->setFillColor(P2_COLOR);
            }
            else if(hex->getFillColor() == P2_COLOR && player == Player::Player1)
            {
                hex->setFillColor(P1_COLOR);
            }
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
            if (hexagon->getFillColor() == sf::Color::White && distance(selectedHexagon, hexagon) < HEX_SIZE * 4.4f)
            {
                moveHexagon(selectedHexagon, hexagon);
                // change the player
                player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
            }
        }
        
        // set the selected hexagon to the hexagon that was clicked
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

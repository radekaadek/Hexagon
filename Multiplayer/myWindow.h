#pragma once
#include <SFML/Graphics.hpp>
#include "Hexagon.h"
#include <cmath>
#include <iostream>
#include "Bot.h"

enum Player
{
    Player1,
    Player2
};

enum GameMode
{
    SinglePlayer,
    MultiPlayer
};

const sf::Color P1_COLOR = sf::Color::Red;
const sf::Color P2_COLOR = sf::Color::Blue;

const int BOARD_SIZE = 9;

const float HEX_VERTICAL_SPACING = HEX_SIZE * 2.0f;
const float HEX_HORIZONTAL_SPACING = HEX_RADIUS * 2.0f;


class myWindow : public sf::RenderWindow
{
myHexagon *selectedHexagon = nullptr;
Bot bot;
GameMode mode = GameMode::SinglePlayer;
public:
    Player player = Player::Player1;
    std::vector<myHexagon *> hexagons{};
    myWindow(sf::VideoMode mode, const sf::String &title, sf::Uint32 style = sf::Style::Default,
             const sf::ContextSettings &settings = sf::ContextSettings()) : RenderWindow(mode, title, style, settings), bot(this)
    {
    }
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
    void innitBoard();
    void redrawBoard()
    {
        for (auto hex : hexagons)
        {
            draw(*hex);
        }
    }

    void handleClick(sf::Event event)
    {
        for (auto hex : hexagons)
        {
            if (hex->getGlobalBounds().contains({float(event.mouseButton.x), float(event.mouseButton.y)}))
            {
                selectHexagon(hex);
            }
        }
    }

    std::vector<myHexagon*> getNeighbours(myHexagon* center);
    std::vector<myHexagon*> getPlayerHexagons(Player player);


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
                if (mode == GameMode::SinglePlayer)
                {
                    // call the bot
                    std::pair<myHexagon, myHexagon> bestMove = bot.getBestMove();
                    moveHexagon(&bestMove.first, &bestMove.second);
                    // change the player
                    player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
                }
            }
        }
        switchOutline(hexagon);
    }

    void switchOutline(myHexagon *hexagon);

    myHexagon *getSelectedHexagon() const
    {
        return selectedHexagon;
    }


};

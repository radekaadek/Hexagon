#pragma once
#include <SFML/Graphics.hpp>
#include "Hexagon.h"
#include <cmath>
#include <unordered_map>
#include <random>
#include <iostream>

const int BOARD_SIZE = 9;

const float HEX_VERTICAL_SPACING = HEX_SIZE * 2.0f;
const float HEX_HORIZONTAL_SPACING = HEX_RADIUS * 2.0f;


class myWindow : public sf::RenderWindow
{
myHexagon *selectedHexagon = nullptr;
bool singlePlayer = true;
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

    static bool checkValidMove(std::unordered_map<myHexagon *, std::vector<myHexagon *>> neighbours)
    {
        for (auto &hex : neighbours)
        {
            if (hex.second.size() == 0)
            {
                return true;
            }
        }
        return false;
    }

    std::unordered_map<myHexagon*, std::vector<myHexagon*>> getAvailableMoves() const
    {
        std::unordered_map<myHexagon *, std::vector<myHexagon *>> moves;
        for (auto hex : hexagons)
        {
            if (hex->getFillColor() == P2_COLOR)
            {
                std::vector<myHexagon *> neighbour = getNeighbours(hex, 4.4f);
                // sort out not white hexagons
                for (auto &hex2 : neighbour)
                {
                    if (hex2->getFillColor() == sf::Color::White)
                    {
                        moves[hex].push_back(hex2);
                    }
                }
            }
        }
        // check if there are any valid moves
        if (moves.size() == 0)
        {
            throw std::runtime_error("No valid moves");
        }
        return moves;
    }

    std::pair<myHexagon*, myHexagon*> getBestMove() const
    {
        // map available hexagons to their neighbours
        std::unordered_map<myHexagon *, std::vector<myHexagon *>> neighbours = getAvailableMoves();
        // check if there are any valid moves
        if (neighbours.size() == 0)
        {
            throw std::runtime_error("No valid moves");
        }
        // random generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, neighbours.size() - 1);
        int random = dis(gen);
        auto it = neighbours.begin();
        std::advance(it, random);
        myHexagon *center = it->first;
        std::vector<myHexagon *> neighbour = it->second;
        std::uniform_int_distribution<> dis2(0, neighbour.size() - 1);
        int random2 = dis2(gen);
        myHexagon *target = neighbour[random2];
        return std::make_pair(center, target);
    }

    std::vector<myHexagon*> getNeighbours(myHexagon* center, float dist = 2.2f) const
    {
        std::vector<myHexagon*> neighbours = {};
        for (auto hex : hexagons)
        {
            if (hex == center)
            {
                continue;
            }
            // check distance between center and hex
            if (distance(center,hex) < HEX_SIZE * dist)
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
    //How many points does each player have
    int getPoints(Player player)
    {
        int points = 0;
        for (auto hex : hexagons)
        {
            if (hex->getFillColor() == P1_COLOR && player == Player::Player1)
            {
                points++;
            } else if (hex->getFillColor() == P2_COLOR && player == Player::Player2)
            {
                points++;
            }
        }
        return points;
    }
    // check if the game is over and return the winner
    std::string checkWinner()
    {
        if (getPoints(Player::Player1) + getPoints(Player::Player2) == 58)
        {
            if (getPoints(Player::Player1) > getPoints(Player::Player2))
            {
                return "Player Red won!";
            }
            else if (getPoints(Player::Player1) < getPoints(Player::Player2))
            {
                return "Player Blue won !";
            }
            else
            {
                return "Tie!";
            }
        }
        else if (getPoints(Player::Player1) == 0)
        {
            // fill the board with blue
            for (auto hex : hexagons)
            {
                hex->setFillColor(P2_COLOR);
            }
            return "Player Blue won!";
        }
        else if (getPoints(Player::Player2) == 0)
        {
            //fill the board with red
            for (auto hex : hexagons)
            {
                hex->setFillColor(P1_COLOR);
            }
            return "Player Blue won !";
        }
        else
        {
            return "";
        }
    }

    void botMove() {
        std::pair<myHexagon*, myHexagon*> move;
        try {
            move = getBestMove();
        }
        catch(std::runtime_error &e)
        {
            player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
            return;
        }
        moveHexagon(move.first, move.second);
        // change the player
        player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
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
                // move the hexagon
                moveHexagon(selectedHexagon, hexagon);
                // change the player
                player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
                if (singlePlayer)
                {
                    botMove();
                }

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
            if (hexagon->getFillColor() == sf::Color::White && distance(selectedHexagon, hexagon) < HEX_SIZE * 4.4f){

            }

        }
    }



};

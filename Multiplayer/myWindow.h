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
    std::vector<myHexagon *> hexagons;
    using sf::RenderWindow::RenderWindow;
    // destructor
    ~myWindow()
    {
        for (auto hex : hexagons)
        {
            delete hex;
        }
            delete selectedHexagon;

    }
    void innitBoard()
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (((i == 0 || i == BOARD_SIZE - 1) && (j == 0 || j == 1 || j == BOARD_SIZE - 1 || j == BOARD_SIZE - 2)) || ((i == 1 || i == BOARD_SIZE - 2) && (j == 0 || j == BOARD_SIZE - 1 || j == BOARD_SIZE - 2)) || ((i == 2 || i == BOARD_SIZE - 3) && (j == 0 || j == BOARD_SIZE - 1)) || ((i == 3 || i == BOARD_SIZE - 4) && (j == BOARD_SIZE - 1)) || (i == 4 && j == 3) || ((i == 3 || i == 5) && j == 4))
                    continue;

                float x = HEX_HORIZONTAL_SPACING * float(i + 1);
                float y = HEX_VERTICAL_SPACING * float(j + 1);

                if (i % 2 != 0)
                {
                    y += HEX_VERTICAL_SPACING / 2.0f;
                }
                auto *hexagon = new myHexagon(sf::Vector2f(x, y), sf::Color::White);
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
    void clearBoard(){
        for (auto hex : hexagons)
        {
            delete hex;
        }
        hexagons.clear();
    }
    void menu() {
        sf::RectangleShape humanVsHumanButton({200, 50});
        humanVsHumanButton.setOutlineColor(sf::Color::White);
        humanVsHumanButton.setOutlineThickness(5);
        humanVsHumanButton.setPosition({400, 300});
        humanVsHumanButton.setFillColor(sf::Color::Cyan);

        sf::RectangleShape humanVsBotButton({200, 50});
        humanVsBotButton.setPosition({400, 370});
        humanVsBotButton.setOutlineColor(sf::Color::White);
        humanVsBotButton.setOutlineThickness(5);
        humanVsBotButton.setFillColor(sf::Color::Blue);

        sf::Font font;
        sf::Text Menu(font);
        sf::Text humanVsHumanText(font);
        sf::Text humanVsBotText(font);

        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Błąd ładowania czcionki." << std::endl;
        }
        Menu.setFont(font);
        Menu.setString("HEXXAGON");
        Menu.setCharacterSize(50);
        Menu.setFillColor(sf::Color::White);
        Menu.setStyle(sf::Text::Bold);
        Menu.setPosition({355, 200});

        humanVsHumanText.setFont(font);
        humanVsHumanText.setString("Multiplayer");
        humanVsHumanText.setCharacterSize(20);
        humanVsHumanText.setFillColor(sf::Color::White);
        humanVsHumanText.setPosition({450, 310});

        humanVsBotText.setFont(font);
        humanVsBotText.setString("Singleplayer");
        humanVsBotText.setCharacterSize(20);
        humanVsBotText.setFillColor(sf::Color::White);
        humanVsBotText.setPosition({450, 380});

        bool modeSelected = false;

        while (!modeSelected) {
            sf::Event event{};
            while (pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    close();
                    return;
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    auto mousePosition = sf::Mouse::getPosition(*this);
                    if (humanVsHumanButton.getGlobalBounds().contains({float(mousePosition.x), float(mousePosition.y)})) {
                        player = Player::Player1;
                        singlePlayer = false;
                        modeSelected = true;
                    } else if (humanVsBotButton.getGlobalBounds().contains({float(mousePosition.x), float(mousePosition.y)})) {
                        player = Player::Player1;
                        singlePlayer = true;
                        modeSelected = true;
                    }
                }
            }

            clear();
            draw(Menu);
            draw(humanVsHumanButton);
            draw(humanVsBotButton);
            draw(humanVsHumanText);
            draw(humanVsBotText);
            display();
        }
    }
    std::unordered_map<myHexagon*, std::vector<myHexagon*>> getAvailableMoves() const
    {
        std::unordered_map<myHexagon *, std::vector<myHexagon *>> moves;
        for (auto hex : hexagons) {
            if (hex->getFillColor() == P2_COLOR && player == Player2) {
                std::vector<myHexagon *> neighbour = getNeighbours(hex, 4.4f);
                // sort out not white hexagons
                for (auto hex2: neighbour) {
                    if (hex2->getFillColor() == sf::Color::White) {
                        moves[hex].push_back(hex2);
                    }
                }
            } else if (hex->getFillColor() == P1_COLOR && player == Player1) {
                std::vector<myHexagon *> neighbour = getNeighbours(hex, 4.4f);
                // sort out not white hexagons
                for (auto hex2: neighbour) {
                    if (hex2->getFillColor() == sf::Color::White) {
                        moves[hex].push_back(hex2);
                    }
                }
            }
        }
        return moves;
    }

    std::pair<myHexagon*, myHexagon*> getBestMove() const
    {
        // map available hexagons to their neighbours
        std::unordered_map<myHexagon *, std::vector<myHexagon *>> neighbours = getAvailableMoves();
        // get first hexagon
        myHexagon *bestHex = neighbours.begin()->first;
        // get first neighbour
        myHexagon *bestNeighbour = neighbours.begin()->second[0];


        int bestScore = 0;
        // for every available hexagon count the number of enemy neighbours
        for (const auto &owned : neighbours)
        {
            for (const auto &neighbour : owned.second)
            {
                // get the neighbours of the potential move
                std::vector<myHexagon *> potentialNeighbours = getNeighbours(neighbour, 2.2f);
                // if the hexagon is close, add 1 to the score
                int score = distance(neighbour, owned.first) < HEX_SIZE*2.2f ? 1 : 0;
                // count the number of enemy neighbours
                for (const auto &potentialNeighbour : potentialNeighbours)
                {
                    if (potentialNeighbour->getFillColor() != owned.first->getFillColor() &&
                        potentialNeighbour->getFillColor() != sf::Color::White)
                    {
                        score += 2;
                    }
                }
                // if the score is better than the current best score, update the best score and the best move
                if (score > bestScore)
                {
                    bestScore = score;
                    bestHex = owned.first;
                    bestNeighbour = neighbour;
                }
            }
        }

        return std::make_pair(bestHex, bestNeighbour);
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

    void moveHexagon(myHexagon *start, myHexagon *end) const{
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
    int getPoints(Player player1)
    {
        int points = 0;
        for (auto hex : hexagons)
        {
            auto color = hex->getFillColor();
            if (color == P1_COLOR && player1 == Player::Player1){
                points++;
            } else if (color == P2_COLOR && player1 == Player::Player2)
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

        move = getBestMove();

        moveHexagon(move.first, move.second);
        // change the player
        player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
    }

    void selectHexagon(myHexagon *hexagon) {
        for (auto hex: hexagons) {
            hex->setOutlineThickness(0);
        }
        // check if a hexagon is already selected
        if (selectedHexagon != nullptr) {
            // check if the color of hexagon is white
            if (hexagon->getFillColor() == sf::Color::White &&
                distance(selectedHexagon, hexagon) < HEX_SIZE * 4.4f) {
                // move the hexagon
                moveHexagon(selectedHexagon, hexagon);

                // change the player
                player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
                if (singlePlayer) {
                    if (getAvailableMoves().empty()) {
                        for (auto hex: hexagons) {
                            if (hex->getFillColor() == sf::Color::White) {
                                hex->setFillColor(P1_COLOR);
                            }
                        }
                    } else {
                        botMove();
                    }
                }

            }
        }
        if (getAvailableMoves().empty()) {
            for (auto hex: hexagons) {
                if (hex->getFillColor() == sf::Color::White) {
                    if (player == Player::Player1)
                        hex->setFillColor(P2_COLOR);
                    else if (player == Player::Player2)
                        hex->setFillColor(P1_COLOR);
                }
            }
        }
        // set the selected hexagon to the hexagon that was clicked
        selectedHexagon = nullptr;
        // if the player matches the color of the hexagon
        // create an outline around the hexagon
        if ((hexagon->getFillColor() == P1_COLOR and player == Player::Player1) ||
            (hexagon->getFillColor() == P2_COLOR and player == Player::Player2)) {
            selectedHexagon = hexagon;
            hexagon->setOutlineColor(sf::Color::Yellow);
            hexagon->setOutlineThickness(5);

            for (auto hex: hexagons) {
                if (hex->getFillColor() == sf::Color::White && distance(hex, hexagon) < HEX_SIZE * 2.2f) {
                    hex->setOutlineColor(sf::Color::Green);
                    hex->setOutlineThickness(3);

                } else if (hex->getFillColor() == sf::Color::White && distance(hex, hexagon) > HEX_SIZE * 2.2f &&
                           distance(hex, hexagon) < HEX_SIZE * 4.4f) {
                    hex->setOutlineColor(sf::Color::Yellow);
                    hex->setOutlineThickness(3);
                }
            }
        }
    }

};
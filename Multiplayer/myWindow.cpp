#include "myWindow.h"

void myWindow::innitBoard()
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

std::vector<myHexagon*> myWindow::getNeighbours(myHexagon* center)
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

void myWindow::switchOutline(myHexagon *hexagon)
{
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

std::vector<myHexagon*> myWindow::getPlayerHexagons(Player player)
{
    std::vector<myHexagon*> playerHexagons = {};
    for (auto hex : hexagons)
    {
        if (hex->getFillColor() == P1_COLOR && player == Player::Player1)
        {
            playerHexagons.push_back(hex);
        }
        else if (hex->getFillColor() == P2_COLOR && player == Player::Player2)
        {
            playerHexagons.push_back(hex);
        }
    }
    return playerHexagons;
}

#include "myWindow.h"

// void myWindow::botMove()
// {
//     // std::pair<myHexagon, myHexagon> move = Bot::getBestMove(this);
//     // moveHexagon(&move.first, &move.second);
// }

// void myWindow::moveHexagon(myHexagon *start, myHexagon *end) {
//     // swap the colors of the hexagons
//     sf::Color temp = start->getFillColor();
//     if (distance(start, end) > HEX_SIZE * 2.2f)
//         start->setFillColor(end->getFillColor());
//     end->setFillColor(temp);
//     // check if nearby hexagons are the opposite color
//     // if they are, change their color to the color of the player
//     std::vector<myHexagon*> neighbours = getNeighbours(end);
//     for (auto hex : neighbours)
//     {
//         if(hex->getFillColor() == P1_COLOR && player == Player::Player2)
//         {
//             hex->setFillColor(P2_COLOR);
//         }
//         else if(hex->getFillColor() == P2_COLOR && player == Player::Player1)
//         {
//             hex->setFillColor(P1_COLOR);
//         }
//     }
// }

void myWindow::handleClick(sf::Vector2f mousePos)
{
    for (auto hex : hexagons)
    {
        if (hex->getGlobalBounds().contains(mousePos))
        {
            selectHexagon(hex);
            break;
        }
    }
}

// void myWindow::selectHexagon(myHexagon *hexagon)
// {
//     for (auto hex : hexagons)
//     {
//         hex->setOutlineThickness(0);
//     }

//     // check if a hexagon is already selected
//     if (selectedHexagon != nullptr)
//     {
//         // check if the color of hexagon is white
//         if (hexagon->getFillColor() == sf::Color::White && distance(selectedHexagon, hexagon) < HEX_SIZE * 4.4f)
//         {
//             moveHexagon(selectedHexagon, hexagon);
//             // change the player
//             player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
//             if (mode == GameMode::SinglePlayer && player == Player::Player2)
//             {
//                 botMove();
//             }
//         }
//     }
// }


#include "Bot.h"
#include <unordered_map>
#include <random>

bool checkValidMove(std::unordered_map<myHexagon*, std::vector<myHexagon*>> neighbours)
{
    for (auto hex : neighbours)
    {
        if (hex.second.size() > 0)
        {
            return true;
        }
    }
    return false;
}

std::pair<myHexagon, myHexagon> Bot::getBestMove() {
    // get all player2 hexagons
    std::vector<myHexagon*> player2Hexagons = window->getPlayerHexagons(Player::Player2);
    // get neighbours of player2 hexagons
    std::unordered_map<myHexagon*, std::vector<myHexagon*>> neighbours = {};
    for (auto hex : player2Hexagons)
    {
        // return only white neighbours
        std::vector<myHexagon*> whiteNeighbours = {};
        for (auto neighbour : window->getNeighbours(hex))
        {
            if (neighbour->getFillColor() == sf::Color::White)
            {
                whiteNeighbours.push_back(neighbour);
            }
        }
        neighbours[hex] = whiteNeighbours;
    }
    // check if there is a valid move, if there isnt throw an exception
    if (checkValidMove(neighbours) == false)
    {
        throw std::bad_exception();
    }
    // return a random move
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, player2Hexagons.size() - 1);
    int randomIndex = dis(gen);
    myHexagon* randomHex = player2Hexagons[randomIndex];
    std::uniform_int_distribution<> dis2(0, neighbours[randomHex].size() - 1);
    int randomIndex2 = dis2(gen);
    myHexagon* randomNeighbour = neighbours[randomHex][randomIndex2];
    return std::pair<myHexagon, myHexagon>(*randomHex, *randomNeighbour);
}
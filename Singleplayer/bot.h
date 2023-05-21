#pragma once
// #include <unordered_map>
// #include <random>
// #include "myWindow.h"

// class Bot
// {
// public:
//     static bool checkValidMove(std::unordered_map<myHexagon *, std::vector<myHexagon *>> neighbours)
//     {
//         for (auto &hex : neighbours)
//         {
//             if (hex.second.size() == 0)
//             {
//                 return true;
//             }
//         }
//         return false;
//     }
//     static std::pair<myHexagon, myHexagon> getBestMove(myWindow *window)
//     {
//         std::unordered_map<myHexagon *, std::vector<myHexagon *>> neighbours;
//         for (auto &hex : window->hexagons)
//         {
//             if (hex->getFillColor() == sf::Color::White)
//             {
//                 std::vector<myHexagon *> neighbour;
//                 for (auto &hex2 : window->hexagons)
//                 {
//                     if (hex2->getFillColor() != sf::Color::White && distance(hex, hex2) <= HEX_SIZE * 1.1f)
//                     {
//                         neighbour.push_back(hex2);
//                     }
//                 }
//                 neighbours.insert({hex, neighbour});
//             }
//         }
//         if (!checkValidMove(neighbours))
//         {
//             return std::make_pair(*window->hexagons[0], *window->hexagons[0]);
//         }
//         // random generator
//         std::random_device rd;
//         std::mt19937 gen(rd());
//         std::uniform_int_distribution<> dis(0, neighbours.size() - 1);
//         int random = dis(gen);
//         auto it = neighbours.begin();
//         std::advance(it, random);
//         myHexagon *center = it->first;
//         std::vector<myHexagon *> neighbour = it->second;
//         std::uniform_int_distribution<> dis2(0, neighbour.size() - 1);
//         int random2 = dis2(gen);
//         myHexagon *target = neighbour[random2];
//         return std::make_pair(*center, *target);
//     }
// };

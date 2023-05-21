#pragma once
#include "myWindow.h"
#include "Hexagon.h"
#include <unordered_map>

class myWindow;

class Bot {
    myWindow* window;
public:
    Bot(myWindow* window) : window(window) {}
    std::pair<myHexagon, myHexagon> getBestMove();
};

bool checkValidMove(std::unordered_map<myHexagon*, std::vector<myHexagon*>> neighbours);

#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "myWindow.h"

int main()
{
    myWindow window(sf::VideoMode({1000, 700}), "Hexxagon");
    sf::Event event;
    window.innitBoard();
    while (window.isOpen())
    {
        window.clear();
        window.redrawBoard();
        //        shape.move({0.03,0});
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                window.handleClick(mousePosition);
            }
        }
        window.display();
    }
    return 0;
}
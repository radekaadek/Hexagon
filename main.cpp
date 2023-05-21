#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "myWindow.h"

int main()
{
    myWindow window(sf::VideoMode({1000, 800}), "Window");
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
                // change the color of the hexagon
                for (auto hex : window.hexagons)
                {
                    if (hex->getGlobalBounds().contains({float(event.mouseButton.x), float(event.mouseButton.y)}))
                    {
                        window.selectHexagon(hex);
                    }
                }
            }
        }
        window.display();
    }
    return 0;
}
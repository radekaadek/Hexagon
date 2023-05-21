#include <SFML/Graphics.hpp>
#include "mywindow.h"

void drawBoard(myWindow &window)
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
            window.drawHexagon(window, sf::Vector2f(x, y), sf::Color::Red);
        }
    }
}

int main()
{
    myWindow window(sf::VideoMode(800, 800), "Hexxagon");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // change colors of all hexagons
                for (auto hex : window.hexagons)
                {
                    hex->setFillColor(sf::Color::Blue);
                }
            }
        }
        window.clear();
        drawBoard(window);
        window.display();
    }

    return 0;
}

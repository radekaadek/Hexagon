#include <SFML/Graphics.hpp>

const int BOARD_SIZE = 9;
const float HEX_SIZE = 40.0f;
const float HEX_RADIUS = HEX_SIZE * 0.866f;
const float HEX_VERTICAL_SPACING = HEX_SIZE * 2.0f;
const float HEX_HORIZONTAL_SPACING = HEX_RADIUS * 2.0f;


void drawHexagon(sf::RenderWindow& window, sf::Vector2f position, sf::Color fillColor) {
    sf::CircleShape hexagon(HEX_SIZE, 6);
    hexagon.setOrigin(HEX_SIZE, HEX_SIZE + 50.0f);
    hexagon.setPosition(position);
    hexagon.setFillColor(fillColor);
    hexagon.rotate(90.0f);
    window.draw(hexagon);
}

void drawBoard(sf::RenderWindow& window) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
              if (((i == 0 || i == BOARD_SIZE-1) && (j == 0 || j == 1 || j == BOARD_SIZE-1 || j== BOARD_SIZE-2))
              || ((i == 1 || i == BOARD_SIZE-2) && (j == 0 || j == BOARD_SIZE-1 || j== BOARD_SIZE-2 ))
              || ((i == 2 || i == BOARD_SIZE-3) && (j == 0 || j == BOARD_SIZE-1))
              || ((i == 3 || i == BOARD_SIZE-4) && ( j == BOARD_SIZE-1))
              || (i == 4 && j == 3)
              || ((i == 3 || i == 5) && j == 4))
               continue;


            float x = HEX_HORIZONTAL_SPACING * (i + 1);
            float y = HEX_VERTICAL_SPACING * (j + 1);
            if (i % 2 != 0) {
                y += HEX_VERTICAL_SPACING / 2.0f;
            }
            drawHexagon(window, sf::Vector2f(x, y), sf::Color::White);

        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Hexxagon");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        drawBoard(window);




        window.display();
    }

    return 0;
}

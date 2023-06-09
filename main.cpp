/**
 * @file main.cpp
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "myWindow.h"

/**
 * @brief Główny punkt wejścia programu.
 *
 * Tworzy okno programu gry hexxagon, ustawia jego parametry, tworzy obiekty klasy myWindow, wywołuje funkcję
 *
 * @return Status wyjścia programu.
 */
int main() {
    myWindow window(sf::VideoMode({1000, 800}), "HEXXAGON");
    window.setFramerateLimit(120);
    sf::Event event{};
    window.innitBoard();
    sf::Font font1;
    if (!font1.loadFromFile("arial.ttf")) {
        std::cout << "Błąd ładowania czcionki." << std::endl;
    }
    //Text who won
    sf::Text text(font1);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition({750, 350});
    //Blue points
    sf::CircleShape shapeBlue(50, 6);
    shapeBlue.setPosition({850, 600});
    shapeBlue.setFillColor(sf::Color::Blue);
    sf::Text text_blue = text;
    text_blue.setCharacterSize(48);
    text_blue.setFillColor(sf::Color::White);
    text_blue.setPosition({800, 620});
    //Red points
    sf::CircleShape shapeRed(50, 6);
    shapeRed.setPosition({850, 100});
    shapeRed.setFillColor(sf::Color::Red);
    sf::Text text_red(font1);
    text_red.setCharacterSize(48);
    text_red.setFillColor(sf::Color::White);
    text_red.setPosition({800, 120});
    //Button Back
    sf::RectangleShape back({70, 40});
    back.setFillColor(sf::Color::Black);
    back.setPosition({15, 15});
    sf::Text text_back(font1);
    text_back.setString("Back");
    text_back.setCharacterSize(24);
    text_back.setFillColor(sf::Color::White);
    text_back.setPosition({20,20});

    window.menu();

    while (window.isOpen()) {
        window.clear();
        window.redrawBoard();
        window.draw(back);
        window.draw(text_back);
        window.draw(shapeBlue);
        window.draw(shapeRed);
        window.draw(text_blue);
        window.draw(text_red);
        window.draw(text);
        text.setString(window.checkWinner());
        text_blue.setString(std::to_string(window.getPoints(Player2)));
        text_red.setString(std::to_string(window.getPoints(Player1)));

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.updateHighscores();
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                for (auto hex: window.hexagons) {
                    if (hex->getGlobalBounds().contains({float(event.mouseButton.x), float(event.mouseButton.y)})) {
                        window.selectHexagon(hex);
                    }
                }
                if (back.getGlobalBounds().contains({float(event.mouseButton.x), float(event.mouseButton.y)})) {
                    window.updateHighscores();
                    window.clearBoard();
                    window.menu();
                    window.innitBoard();
                }

            }
            window.display();
        }
    }
    return 0;
}

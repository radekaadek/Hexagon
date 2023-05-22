#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "myWindow.h"

int main() {
    myWindow window(sf::VideoMode({1000, 800}), "Window");
    sf::Event event;
    window.innitBoard();
    sf::Font font1;
    font1.loadFromFile("arial.ttf");
    //Text
    sf::Text basicBitch;
    basicBitch.setFont(font1);
    basicBitch.setCharacterSize(24);
    basicBitch.setFillColor(sf::Color::White);
    basicBitch.setPosition({750, 350});
    //create a shape
    sf::CircleShape shapeBlue(50, 6);
    sf::CircleShape shapeRed(50, 6);
    //Blue point
    shapeBlue.setPosition({850, 600});
    shapeBlue.setFillColor(sf::Color::Blue);
    sf::Text text_blue = basicBitch;
    text_blue.setCharacterSize(48);
    text_blue.setFillColor(sf::Color::White);
    text_blue.setPosition({800, 620});
    //Blue point
    shapeRed.setPosition({850, 100});
    shapeRed.setFillColor(sf::Color::Red);
    sf::Text text_red;
    text_red.setFont(font1);
    text_red.setCharacterSize(48);
    text_red.setFillColor(sf::Color::White);
    text_red.setPosition({800, 120});
    while (window.isOpen()) {
        window.clear();
        window.redrawBoard();
        window.draw(shapeBlue);
        window.draw(shapeRed);
        window.draw(text_blue);
        window.draw(text_red);
        window.draw(basicBitch);
        basicBitch.setString(window.checkWinner());
        text_blue.setString(std::to_string(window.getPoints(Player2)));
        text_red.setString(std::to_string(window.getPoints(Player1)));

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                // change the color of the hexagon
                for (auto hex: window.hexagons) {
                    if (hex->getGlobalBounds().contains({float(event.mouseButton.x), float(event.mouseButton.y)})) {
                        window.selectHexagon(hex);
                    }
                }
            }
            window.display();
        }
    }
    return 0;
}
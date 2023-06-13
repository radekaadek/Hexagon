/**
 * @file Hexagon.h
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

/**
 * @brief Stała określająca rozmiar sześciokąta.
 */
const float HEX_SIZE = 40.0f;

/**
 * @brief Stała określająca promień sześciokąta.
 */
const float HEX_RADIUS = HEX_SIZE * 0.866f;

/**
 * @brief Kolor gracza 1.
 */
const sf::Color P1_COLOR = sf::Color::Red;

/**
 * @brief Kolor gracza 2.
 */
const sf::Color P2_COLOR = sf::Color::Blue;

/**
 * @brief Enum określający graczy.
 */
enum Player
{
    Player1,
    Player2
};

/**
 * @brief Klasa do tworzenia planszy.
 */
class myHexagon : public sf::CircleShape
{
public:
    /**
     * @brief Konstruktor sześciokąta.
     *
     * @param position Pozycja sześciokąta.
     * @param color Kolor sześciokąta.
     */
    myHexagon(const sf::Vector2f &position, const sf::Color &color);

};

/**
 * @brief Oblicza odległość między dwoma sześciokątami.
 *
 * @param a Pierwszy sześciokąt.
 * @param b Drugi sześciokąt.
 * @return Odległość między sześciokątami.
 */
float distance(const myHexagon *a, const myHexagon *b);

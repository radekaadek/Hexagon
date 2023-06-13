/**
 * @file myWindow.h
 *
 * @brief Plik nagłówkowy klasy myWindow.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "Hexagon.h"
#include <cmath>
#include <unordered_map>
#include <random>
#include <iostream>
#include <fstream>

/**
 * @brief wielkość planszy.
 */
const int BOARD_SIZE = 9;
/**
 * @brief Pionowy odstęp między sześciokoątami.
 */
const float HEX_VERTICAL_SPACING = HEX_SIZE * 2.0f;
/**
 * @brief Poziomy odstęp między sześciokoątami.
 */
const float HEX_HORIZONTAL_SPACING = HEX_RADIUS * 2.0f;


/**
 * @brief Klasa do tworzenia oknien i funkcji.
 */

class myWindow : public sf::RenderWindow
{
public:
    myHexagon *selectedHexagon = nullptr; /**< Wzskaźnik na wybrany heksagon */
    bool singlePlayer = true; /**< Zmienna określająca czy gra jest na jednego gracza */
    bool closeW = false; /**< Zmienna określająca czy okno jest zamknięte */
    Player player = Player::Player1; /**< Zmienna określająca gracza */
    std::vector<myHexagon *> hexagons; /**< Wektor przechowujący wszystkie sześciokąty na planszy */
    using sf::RenderWindow::RenderWindow; /**< Dziedziczenie konstruktora z klasy sf::RenderWindow */

    /**
     * @brief Wyświetla główne menu i obsługuje wejście użytkownika w celu wybrania gry .
     */
    void menu();
    /**
     * @brief Wyświetla ekran z najlepszymi wynikami.
     */
    void bestScore();
    /**
     * @brief aktualizuje tablice wyników.
     */
    void updateHighscores();
    /**
     * @brief Destruktor.
     */
    ~myWindow();
    /**
     * @brief Inicjalizuje planszę do gry hexxagon.
     */
    void innitBoard();
    /**
     * @brief Przerysowuje planszę gry.
     */
    void redrawBoard();
    /**
     * @brief Czyści planszę gry.
     */
    void clearBoard();
    /**
    * @brief Pobiera dostępne ruchy dla aktualnego gracza.
    *
    * @return Mapa dostępnych ruchów, gdzie kluczem jest wybrany sześciokąt, a wartością jest wektor możliwych docelowych ruchów sześciokąta.
    */
    std::unordered_map<myHexagon*, std::vector<myHexagon*>> getAvailableMoves() const;
    /**
     * @brief Oblicza potencjalny wynik ruchu z sześciokąta startowego do sześciokąta końcowego dla bota.
     *
     * @param start Hexagon startowy (pozycja sześciokąta).
     * @param end Hexagon końcowy (jego ruch na inny sześciokąta).
     *
     * @return Potencjalny wynik ruchu który zdobędzie jak najwięcej sześciokątów przeciwnika.
     */
    int getPotentialScore(const myHexagon *start, const myHexagon *end) const;
    /**
     * @brief Zwraca losowy ruch dla bota.
     *
     * @brief moves Dostępne ruchy dla bota.
     *
     * @return Para sześciokątów, gdzie pierwszy to sześciokąt startowy, a drugi to sześciokąt docelowy.
     */
    static std::pair<myHexagon*, myHexagon*> getRandomMove(const std::vector<std::pair<myHexagon*, myHexagon*>> moves);
    /**
     * @brief Wykonuje ruch sześciokąta z startowego na docelowy dla bota.
     *
     * @param start Hexagon startowy.
     * @param end Hexagon docelowy.
     *
     * @return zwraca najlepszy ruch dla bota
     */
    std::pair<myHexagon*, myHexagon*> getBestMove() const;

    /**
     * @brief Wykonuje ruch bota.
     */
    void botMove();
    /**
    * @brief Pobiera sąsiadujące heksagony.
    *
    * @param center Hexagon, dla którego szukamy sąsiadów.
    * @param dist Odległość, do której należy sprawdzić sąsiadów (domyślnie 2.2f).
    *
    * @return Wektor wskaźników wszystkich sąsiadów.
    */
    std::vector<myHexagon*> getNeighbours(const myHexagon* center, float dist) const;
    /**
     * @brief Wykonuje ruch sześciokąta z startowego na docelowy dla gracza.
     *
     * @param start Heksagon startowy.
     * @param end Heksagon docelowy.
     */
    void moveHexagon(myHexagon *start, myHexagon *end) const;

    /**
     * @brief Zwraca punkty gracza.
     *
     * @param player1 Gracz, dla którego zwracamy punkty.
     *
     * @return Ilość punktów gracza.
     */
    int getPoints(Player player1) const;

    /**
     * @brief Sprawdza, czy gra się zakończyła i zwraca zwycięzcę.
     *
     * @return Napis z wynikiem gry.
     */
    std::string checkWinner() const;
    /**
     * @brief Wybiera sześciokąt i pokazuje możliwe ruchy
     *  i pokrywa plansze odpowiednim kolorem jeśli przeciwnik nie ma ruchu.
     *
     * @param hexagon Wybrany Hexagon.
     */
    void selectHexagon(myHexagon *hexagon);
};
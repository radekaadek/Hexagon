#include "myWindow.h"

void myWindow::menu() {

    sf::Font font;
    sf::Text Menu(font);
    sf::Text humanVsHumanText(font);
    sf::Text humanVsBotText(font);
    sf::Text bestScoreText(font);

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Błąd ładowania czcionki." << std::endl;
    }
    //Menu Title
    Menu.setFont(font);
    Menu.setString("HEXXAGON");
    Menu.setCharacterSize(50);
    Menu.setFillColor(sf::Color::White);
    Menu.setStyle(sf::Text::Bold);
    Menu.setPosition({355, 200});
    //Multiplayer Button
    sf::RectangleShape humanVsHumanButton({200, 50});
    humanVsHumanButton.setOutlineColor(sf::Color::White);
    humanVsHumanButton.setOutlineThickness(3);
    humanVsHumanButton.setPosition({400, 300});
    humanVsHumanButton.setFillColor(sf::Color::Black);

    humanVsHumanText.setFont(font);
    humanVsHumanText.setString("Multiplayer");
    humanVsHumanText.setCharacterSize(20);
    humanVsHumanText.setFillColor(sf::Color::White);
    humanVsHumanText.setPosition({450, 310});
    //Singleplayer Button
    sf::RectangleShape humanVsBotButton({200, 50});
    humanVsBotButton.setPosition({400, 370});
    humanVsBotButton.setOutlineColor(sf::Color::White);
    humanVsBotButton.setOutlineThickness(3);
    humanVsBotButton.setFillColor(sf::Color::Black);

    humanVsBotText.setFont(font);
    humanVsBotText.setString("Singleplayer");
    humanVsBotText.setCharacterSize(20);
    humanVsBotText.setFillColor(sf::Color::White);
    humanVsBotText.setPosition({450, 380});
    //Best Score Button
    sf::RectangleShape bestScore({200, 50});
    bestScore.setPosition({400, 440});
    bestScore.setOutlineColor(sf::Color::White);
    bestScore.setOutlineThickness(3);
    bestScore.setFillColor(sf::Color::Black);

    bestScoreText.setFont(font);
    bestScoreText.setString("Best Score");
    bestScoreText.setCharacterSize(20);
    bestScoreText.setFillColor(sf::Color::White);
    bestScoreText.setPosition({450, 450});

    bool modeSelected = false;

    while (!modeSelected) {
        sf::Event event{};
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                close();
                return;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePosition = sf::Mouse::getPosition(*this);
                if (humanVsHumanButton.getGlobalBounds().contains({float(mousePosition.x), float(mousePosition.y)})) {
                    player = Player::Player1;
                    singlePlayer = false;
                    modeSelected = true;
                } else if (humanVsBotButton.getGlobalBounds().contains({float(mousePosition.x), float(mousePosition.y)})) {
                    player = Player::Player1;
                    singlePlayer = true;
                    modeSelected = true;
                } else if (bestScore.getGlobalBounds().contains({float(mousePosition.x), float(mousePosition.y)})) {
                    this->bestScore();
                    if (closeW) {
                        close();
                        return;
                    }

                }
            }
        }

        clear();
        draw(Menu);
        draw(humanVsHumanButton);
        draw(humanVsBotButton);
        draw(bestScore);
        draw(humanVsHumanText);
        draw(humanVsBotText);
        draw(bestScoreText);
        display();
    }
}
void myWindow::bestScore() {

    sf::Font font;
    sf::Text bestScore(font);
    sf::Text backButtonText(font);
    sf::Text playerVsBot(font);

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Błąd ładowania czcionki." << std::endl;
    }
    //Best Score Title
    bestScore.setFont(font);
    bestScore.setString("Best Score");
    bestScore.setCharacterSize(50);
    bestScore.setFillColor(sf::Color::White);
    bestScore.setStyle(sf::Text::Bold);
    bestScore.setPosition({355, 180});


    playerVsBot.setFont(font);
    playerVsBot.setString("Player vs Bot");
    playerVsBot.setCharacterSize(30);
    playerVsBot.setFillColor(sf::Color::White);
    playerVsBot.setPosition({390, 240});

    //Back Button
    sf::RectangleShape backButton({200, 50});
    backButton.setOutlineColor(sf::Color::White);
    backButton.setOutlineThickness(3);
    backButton.setPosition({400, 500});
    backButton.setFillColor(sf::Color::Black);

    backButtonText.setFont(font);
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(20);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition({450, 510});

    //Best Score
    sf::Text score(font);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::White);
    bestScore.setStyle(sf::Text::Bold);
    score.setPosition({450, 280});
    std::ifstream fileIn("bestScore.txt");
    std::string line;
    std::string fileText;
    int x = 5;
    while (std::getline(fileIn, line) && x > 0){
        fileText += line + "\n";
        x--;
    }
    fileIn.close();
    score.setString(fileText);

    bool back = false;

    while (!back) {
        sf::Event event{};
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                close();
                closeW = true;
                return;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePosition = sf::Mouse::getPosition(*this);
                if (backButton.getGlobalBounds().contains({float(mousePosition.x), float(mousePosition.y)})) {
                    back = true;
                }
            }
        }

        clear();
        draw(bestScore);
        draw(backButton);
        draw(backButtonText);
        draw(playerVsBot);
        draw(score);
        display();
    }
}
void myWindow::updateHighscores() {
    if (getPoints(Player1) + getPoints(Player2) != 58) {
        return;
    }
    if (!singlePlayer) {
        return;
    }
    int player1Score = getPoints(Player1);
    std::vector<int> scores;

    std::ifstream bestScoreFile;
    bestScoreFile.open("bestScore.txt");
    if (bestScoreFile) {
        std::string line;
        while (std::getline(bestScoreFile, line)) {
            std::string score;
            for (char x : line) {
                if (x == ':') {
                    break;
                }
                score += x;
            }
            scores.push_back(std::stoi(score));
        }
    }

    bestScoreFile.close();
    scores.push_back(player1Score);
    std::sort(scores.begin(), scores.end(),[](int x, int y) -> bool {
                  return x > y;
              }
    );
    if (scores.size() > 5) {
        scores.pop_back();
    }
    std::ofstream bestScoreFileOut("bestScore.txt");
    for (auto score : scores) {
        bestScoreFileOut << std::to_string(score) << ":" << std::to_string(58-score) << std::endl;
    }
    bestScoreFileOut.close();
}
myWindow::~myWindow()
{
    for (auto hex : hexagons)
    {
        delete hex;
    }
}
void myWindow::innitBoard()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (((i == 0 || i == BOARD_SIZE - 1) && (j == 0 || j == 1 || j == BOARD_SIZE - 1 || j == BOARD_SIZE - 2)) || ((i == 1 || i == BOARD_SIZE - 2) && (j == 0 || j == BOARD_SIZE - 1 || j == BOARD_SIZE - 2)) || ((i == 2 || i == BOARD_SIZE - 3) && (j == 0 || j == BOARD_SIZE - 1)) || ((i == 3 || i == BOARD_SIZE - 4) && (j == BOARD_SIZE - 1)) || (i == 4 && j == 3) || ((i == 3 || i == 5) && j == 4))
                continue;

            float x = HEX_HORIZONTAL_SPACING * float(i + 1);
            float y = HEX_VERTICAL_SPACING * float(j + 1);

            if (i % 2 != 0)
            {
                y += HEX_VERTICAL_SPACING / 2.0f;
            }
            auto *hexagon = new myHexagon(sf::Vector2f(x, y), sf::Color::White);
            if ((i == 4 && j == 0) || (i == 0 && j == 6) || (i == BOARD_SIZE - 1 && j == 6))
            {
                hexagon->setFillColor(sf::Color::Red);
            }
            else if ((i == 4 && j == 8) || (i == 0 && j == 2) || (i == BOARD_SIZE - 1 && j == 2))
            {
                hexagon->setFillColor(sf::Color::Blue);
            }
            draw(*hexagon);
            hexagons.push_back(hexagon);
        }
    }
}
void myWindow::redrawBoard()
{
    for (auto hex : hexagons)
    {
        draw(*hex);
    }
}
void myWindow::clearBoard() {
    for (auto hex : hexagons)
    {
        delete hex;
    }
    hexagons.clear();
}
std::unordered_map<myHexagon*, std::vector<myHexagon*>> myWindow::getAvailableMoves() const
{
    std::unordered_map<myHexagon *, std::vector<myHexagon *>> moves;
    for (auto hex : hexagons) {
        if (hex->getFillColor() == P2_COLOR && player == Player2) {
            std::vector<myHexagon *> neighbour = getNeighbours(hex, 4.4f);
            for (auto hex2: neighbour) {
                if (hex2->getFillColor() == sf::Color::White) {
                    moves[hex].push_back(hex2);
                }
            }
        } else if (hex->getFillColor() == P1_COLOR && player == Player1) {
            std::vector<myHexagon *> neighbour = getNeighbours(hex, 4.4f);
            for (auto hex2: neighbour) {
                if (hex2->getFillColor() == sf::Color::White) {
                    moves[hex].push_back(hex2);
                }
            }
        }
    }
    return moves;
}
int myWindow::getPotentialScore(const myHexagon *start, const myHexagon *end) const
{
    int score = distance(start, end) < HEX_SIZE*2.2f ? 1 : 0;
    // get the neighbours of the potential move
    std::vector<myHexagon *> potentialNeighbours = getNeighbours(end, 2.2f);
    // count the number of enemy neighbours
    for (const auto &potentialNeighbour : potentialNeighbours)
    {
        if (potentialNeighbour->getFillColor() != start->getFillColor() &&
            potentialNeighbour->getFillColor() != sf::Color::White)
        {
            score += 2;
        }
    }
    return score;
}
std::pair<myHexagon*, myHexagon*> myWindow::getRandomMove(const std::vector<std::pair<myHexagon*, myHexagon*>> moves)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, moves.size() - 1);
    return moves[dis(gen)];
}
std::pair<myHexagon*, myHexagon*> myWindow::getBestMove() const
{
    std::unordered_map<myHexagon *, std::vector<myHexagon *>> neighbours = getAvailableMoves();
    std::vector<std::pair<myHexagon *, myHexagon *>> bestMoves;

    int bestScore = 0;
    for (const auto &owned : neighbours)
    {
        for (const auto &neighbour : owned.second)
        {
            std::vector<myHexagon *> potentialNeighbours = getNeighbours(neighbour, 2.2f);
            int score = getPotentialScore(owned.first, neighbour);
            if (score > bestScore)
            {
                bestScore = score;
                bestMoves = {std::make_pair(owned.first, neighbour)};
            }
            else if (score == bestScore)
            {
                bestMoves.push_back(std::make_pair(owned.first, neighbour));
            }
        }
    }

    return getRandomMove(bestMoves);
}
void myWindow::botMove() {
    std::pair<myHexagon*, myHexagon*> move;

    move = getBestMove();

    moveHexagon(move.first, move.second);
    player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
}
std::vector<myHexagon*> myWindow::getNeighbours(const myHexagon* center, float dist = 2.2f) const
{
    std::vector<myHexagon*> neighbours = {};
    for (auto hex : hexagons)
    {
        if (hex == center)
        {
            continue;
        }
        if (distance(center,hex) < HEX_SIZE * dist)
        {
            neighbours.push_back(hex);
        }
    }
    return neighbours;
}
void myWindow::moveHexagon(myHexagon *start, myHexagon *end) const{
    sf::Color temp = start->getFillColor();
    if (distance(start, end) > HEX_SIZE * 2.2f)
        start->setFillColor(end->getFillColor());
    end->setFillColor(temp);
    // check if nearby hexagons are the opposite color
    // if they are, change their color to the color of the player
    std::vector<myHexagon*> neighbours = getNeighbours(end);
    for (auto hex : neighbours)
    {
        if(hex->getFillColor() == P1_COLOR && player == Player::Player2)
        {
            hex->setFillColor(P2_COLOR);
        }
        else if(hex->getFillColor() == P2_COLOR && player == Player::Player1)
        {
            hex->setFillColor(P1_COLOR);
        }
    }
}
int myWindow::getPoints(Player player1) const
{
    int points = 0;
    for (auto hex : hexagons)
    {
        auto color = hex->getFillColor();
        if (color == P1_COLOR && player1 == Player::Player1){
            points++;
        } else if (color == P2_COLOR && player1 == Player::Player2)
        {
            points++;
        }
    }
    return points;
}
std::string myWindow::checkWinner() const {
    if (getPoints(Player::Player1) == 0) {
        // fill the board with blue
        for (auto hex: hexagons) {
            hex->setFillColor(P2_COLOR);
        }
    }
    if (getPoints(Player::Player2) == 0) {
        //fill the board with red
        for (auto hex: hexagons) {
            hex->setFillColor(P1_COLOR);
        }
    }
    if (getPoints(Player::Player1) + getPoints(Player::Player2) == 58) {
        if (getPoints(Player::Player1) > getPoints(Player::Player2)) {
            return "Player Red won !";
        } else if (getPoints(Player::Player1) < getPoints(Player::Player2)) {
            return "Player Blue won !";
        } else {
            return "Tie!";
        }
    } else {
        return "";
    }
}
void myWindow::selectHexagon(myHexagon *hexagon) {
    for (auto hex: hexagons) {
        hex->setOutlineThickness(0);
    }
    // check if a hexagon is already selected
    if (selectedHexagon != nullptr) {
        // check if the color of hexagon is white
        if (hexagon->getFillColor() == sf::Color::White &&
            distance(selectedHexagon, hexagon) < HEX_SIZE * 4.4f) {
            moveHexagon(selectedHexagon, hexagon);

            player = (player == Player::Player1) ? Player::Player2 : Player::Player1;
            if (singlePlayer) {
                if (getAvailableMoves().empty()) {
                    for (auto hex: hexagons) {
                        if (hex->getFillColor() == sf::Color::White) {
                            hex->setFillColor(P1_COLOR);
                        }
                    }
                } else {
                    botMove();
                }
            }

        }
    }
    if (getAvailableMoves().empty()) {
        for (auto hex: hexagons) {
            if (hex->getFillColor() == sf::Color::White) {
                if (player == Player::Player1)
                    hex->setFillColor(P2_COLOR);
                else if (player == Player::Player2)
                    hex->setFillColor(P1_COLOR);
            }
        }
    }
    selectedHexagon = nullptr;
    // create an outline around the hexagon
    if ((hexagon->getFillColor() == P1_COLOR and player == Player::Player1) ||
        (hexagon->getFillColor() == P2_COLOR and player == Player::Player2)) {
        selectedHexagon = hexagon;
        hexagon->setOutlineColor(sf::Color::Yellow);
        hexagon->setOutlineThickness(5);

        for (auto hex: hexagons) {
            if (hex->getFillColor() == sf::Color::White && distance(hex, hexagon) < HEX_SIZE * 2.2f) {
                hex->setOutlineColor(sf::Color::Green);
                hex->setOutlineThickness(3);

            } else if (hex->getFillColor() == sf::Color::White && distance(hex, hexagon) > HEX_SIZE * 2.2f &&
                       distance(hex, hexagon) < HEX_SIZE * 4.4f) {
                hex->setOutlineColor(sf::Color::Yellow);
                hex->setOutlineThickness(3);
            }
        }
    }
}
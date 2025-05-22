// Copyright 2025 Cameron Gagne

#include "Sokoban.hpp"

namespace SB {
Sokoban::Sokoban() : boardHeight(0), boardWidth(0),
playerOrientation(Direction::Down), playerLocation(0, 0) {
    groundTexture.loadFromFile("ground_01.png");
    playerTextureUp.loadFromFile("player_08.png");
    playerTextureDown.loadFromFile("player_05.png");
    playerTextureLeft.loadFromFile("player_20.png");
    playerTextureRight.loadFromFile("player_17.png");
    wallTexture.loadFromFile("block_06.png");
    crateTexture.loadFromFile("crate_03.png");
    storageTexture.loadFromFile("environment_03.png");
}
Sokoban::Sokoban(const std::string&) {}

unsigned int Sokoban::pixelHeight() const {
    return boardWidth * TILE_SIZE;
}

unsigned int Sokoban::pixelWidth() const {
    return boardHeight * TILE_SIZE;
}

unsigned int Sokoban::height() const {
    return boardHeight;
}

unsigned int Sokoban::width() const {
    return boardWidth;
}

sf::Vector2u Sokoban::playerLoc() const {
    return playerLocation;
}

void Sokoban::forEachTile(std::function<void(unsigned int, unsigned int)> func) const {
    for (unsigned int i = 0; i < boardHeight; i++) {
        for (unsigned int j = 0; j < boardWidth; j++) {
            func(i, j);
        }
    }
}

bool Sokoban::isWon() const {
    bool openSpaceFlag = false;
    bool boxFlag = false;

    // Use a lambda expression as a parameter
    forEachTile([&](unsigned int i, unsigned int j) {
        if (!(boardObjects[i][j] == 'A' && board[i][j] == 'a')) {
            if (boardObjects[i][j] == 'A')
                boxFlag = true;
            if (board[i][j] == 'a')
                openSpaceFlag = true;
        }
    });

    return !(boxFlag && openSpaceFlag);
}

void Sokoban::movePlayer(Direction dir) {
    int dx = 0, dy = 0;
    playerOrientation = dir;

    switch (dir) {
        case Direction::Left:  dx = -1; break;
        case Direction::Right: dx = 1;  break;
        case Direction::Up:    dy = -1; break;
        case Direction::Down:  dy = 1;  break;
    }

    int px = playerLocation.x;
    int py = playerLocation.y;
    int tx = px + dx;  // target cell
    int ty = py + dy;
    int bx = px + 2 * dx;  // beyond box
    int by = py + 2 * dy;

    // Bounds check
    if (tx >= static_cast<int>(boardWidth) || ty >= static_cast<int>(boardHeight) ||
    tx < 0 || ty < 0) return;

    char& targetObj = boardObjects[ty][tx];
    char& targetTile = board[ty][tx];

    if (targetObj == 'A') {
        if (bx >= static_cast<int>(boardWidth) ||
        by >= static_cast<int>(boardHeight) || bx < 0 || by < 0) return;
        char& beyondObj = boardObjects[by][bx];
        char& beyondTile = board[by][bx];

        if (beyondObj != 'A' && beyondTile != '#') {
            beyondObj = 'A';
        } else {
            return;  // blocked
        }

        targetObj = '@';
        boardObjects[py][px] = 'n';
        playerLocation = { static_cast<unsigned>(tx), static_cast<unsigned>(ty) };
    } else if (targetTile == '.' || targetTile == 'a') {
        boardObjects[py][px] = 'n';
        targetObj = '@';
        playerLocation = { static_cast<unsigned>(tx), static_cast<unsigned>(ty) };
    }
}

void Sokoban::reset() {
    playerOrientation = Direction::Down;
    // Copy the original board and objects using std::copy from algorithm library
    std::copy(originalBoard.begin(), originalBoard.end(), board.begin());
    std::copy(originalBoardObjects.begin(), originalBoardObjects.end(), boardObjects.begin());

    // Use a lambda expression as a parameter
    forEachTile([&](unsigned int i, unsigned int j) {
            if (boardObjects[i][j] == '@') {
                playerLocation.x = j;
                playerLocation.y = i;
                return;
            }
    });
}

void Sokoban::undo() {}  // Optional XC
void Sokoban::redo() {}  // Optional XC

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;

    forEachTile([&](unsigned int i, unsigned int j) {
        sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
        switch (board[i][j]) {
            case '#':  // Wall
                sprite.setTexture(wallTexture);
                target.draw(sprite, states);
                break;

            case 'a':  // Storage Location
                sprite.setTexture(groundTexture);
                target.draw(sprite, states);
                sprite.setTexture(storageTexture);
                target.draw(sprite, states);
                break;

            default:  // Ground
                sprite.setTexture(groundTexture);
                target.draw(sprite, states);
                break;
        }

        switch (boardObjects[i][j]) {
            case '@':  // XC draw player in correct Orientation
                switch (playerOrientation) {
                case Direction::Up:
                    sprite.setTexture(playerTextureUp);
                    break;

                case Direction::Right:
                    sprite.setTexture(playerTextureRight);
                    break;

                case Direction::Left:
                    sprite.setTexture(playerTextureLeft);
                    break;

                default:
                    sprite.setTexture(playerTextureDown);
                    break;
                }
                target.draw(sprite, states);
                break;

            case 'A':  // Box
                sprite.setTexture(crateTexture);
                target.draw(sprite, states);
                break;

            default:  // Nothing
                break;
        }
    });
}

std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    for (unsigned int i = 0; i < s.boardHeight; i++) {
        for (unsigned int j = 0; j < s.boardWidth; j++) {
            if (s.boardObjects[i][j] == 'n')
                out << s.board[i][j];
            else if (s.boardObjects[i][j] == 'A' && s.board[i][j] == 'a')
                out << '1';
            else
                out << s.boardObjects[i][j];
        }
        out << std::endl;
    }
    return out;
}
std::istream& operator>>(std::istream& in, Sokoban& s) {
    double width, height;
    char blockType;
    in >> height >> width;
    s.boardHeight = height;
    s.boardWidth = width;

    s.board.resize(height);
    s.boardObjects.resize(height);
    s.originalBoard.resize(height);
    s.originalBoardObjects.resize(height);

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            in >> blockType;
            if (blockType == '.' || blockType == '#' || blockType == 'a') {
                s.board[i].push_back(blockType);
                s.boardObjects[i].push_back('n');
                s.originalBoard[i].push_back(blockType);
                s.originalBoardObjects[i].push_back('n');
            } else if (blockType == '1') {
                s.board[i].push_back('a');
                s.originalBoard[i].push_back('a');
                s.boardObjects[i].push_back('A');
                s.originalBoardObjects[i].push_back('A');
            } else {
                s.boardObjects[i].push_back(blockType);
                s.board[i].push_back('.');
                s.originalBoardObjects[i].push_back(blockType);
                s.originalBoard[i].push_back('.');
                if (blockType == '@') {
                    s.playerLocation.x = j;
                    s.playerLocation.y = i;
                }
            }
        }
    }
    return in;
}
}  // namespace SB

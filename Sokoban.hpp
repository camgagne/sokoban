// Copyright 2025 Cameron Gagne

#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <SFML/Graphics.hpp>

namespace SB {
enum class Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;

    Sokoban();
    explicit Sokoban(const std::string& s);  // Optional

    unsigned int pixelHeight() const;  // Optional
    unsigned int pixelWidth() const;  // Optional

    unsigned int height() const;
    unsigned int width() const;

    sf::Vector2u playerLoc() const;

    bool isWon() const;

    void movePlayer(Direction dir);
    void reset();

    void undo();  // Optional XC
    void redo();  // Optional XC

    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
    friend std::istream& operator>>(std::istream& in, Sokoban& s);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    unsigned int boardHeight;
    unsigned int boardWidth;
    Direction playerOrientation;
    sf::Vector2u playerLocation;
    std::vector<std::vector<char>> board;
    std::vector<std::vector<char>> boardObjects;
    std::vector<std::vector<char>> originalBoard;
    std::vector<std::vector<char>> originalBoardObjects;
    sf::Texture groundTexture;
    sf::Texture playerTextureUp;
    sf::Texture playerTextureDown;
    sf::Texture playerTextureLeft;
    sf::Texture playerTextureRight;
    sf::Texture wallTexture;
    sf::Texture crateTexture;
    sf::Texture storageTexture;
    // Uses a lambda expression as a parameter
    void forEachTile(std::function<void(unsigned int, unsigned int)> func) const;
};
}  // namespace SB

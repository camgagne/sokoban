// Copyright 2025 Cameron Gagne

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"


int main(int argc, char *argv[]) {
  SB::Sokoban sokoban;

  std::ifstream inputFile;
  inputFile.open(argv[1]);

  inputFile >> sokoban;

  sf::RenderWindow window(sf::VideoMode(sokoban.pixelHeight(), sokoban.pixelWidth()), "Sokoban");

  // Game win message
  sf::Font font;
  font.loadFromFile("font.ttf");
  sf::Text text;
  text.setFont(font);
  text.setString("Game Won!");
  text.setCharacterSize(24);
  text.setPosition((sokoban.pixelHeight()/2)-80, (sokoban.pixelWidth()/2)-15);

  // Load sound to play
  sf::SoundBuffer buffer;
  buffer.loadFromFile("sound.wav");
  sf::Sound sound;
  sound.setBuffer(buffer);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (!sokoban.isWon()) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sokoban.movePlayer(SB::Direction::Left);
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sokoban.movePlayer(SB::Direction::Right);
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sokoban.movePlayer(SB::Direction::Up);
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sokoban.movePlayer(SB::Direction::Down);
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        sokoban.reset();
      }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
      sokoban.reset();
    }


    window.clear();
    window.draw(sokoban);
    if (sokoban.isWon())
      window.draw(text);
    window.display();

    // Play sound for XC :)
    if (sokoban.isWon() && sound.getStatus() != sf::Sound::Playing) {
      sound.play();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::cout << sokoban.playerLoc().x << ", " << sokoban.playerLoc().y << std::endl;
  std::cout << sokoban << std::endl;
  return 0;
}

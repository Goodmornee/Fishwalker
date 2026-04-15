#include "game.h"

#include <SFML/Graphics.hpp>

Game::Game(int heroX, int heroY, int monsterX, int monsterY, int cellSize,
           int mapWidth, int mapHeight)
    : window(sf::VideoMode({800, 600}), "Fishwalker"),
      window.setFramerateLimit(60) {};
void Game::run() {
  while (window.isOpen());
  processInput();
  update();
  render();
};

void Game::processInput() {};
void Game::update() {};
void Game::render() {};

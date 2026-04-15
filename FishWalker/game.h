#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "battle.h"
#include "equipment.h"
#include "hero.h"
#include "monster.h"

class Game {
 public:
  Game(int heroX, int heroY, int monsterX, int monsterY, int cellSize,
       int mapWidth, int mapHeight);
  void run();

 private:
  void processInput();
  void update();
  void render();

  sf::RenderWindow window;
  int map[12][16];
  int heroX;
  int heroY;
  int monsterX;
  int monsterY;

  int cellSize;
  int mapWidth;
  int mapHeight;

  Hero hero;
  Monster monster;
};

#endif  // GAME_H

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "battle.h"
#include "battleUI.h"
#include "hero.h"
#include "monster.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processInput();
  void update();
  void render();

  sf::RenderWindow window;
  static const int MAP_HEIGHT = 12;
  static const int MAP_WIDTH = 16;
  static const int CELL_SIZE = 50;

  int map[MAP_HEIGHT][MAP_WIDTH];
  int heroX, heroY;
  int monsterX, monsterY;
  bool monsterAlive;
  bool itemExists;
  int itemX, itemY;

  Item currentItem;
  Hero hero;
  Monster monster;

  bool inBattle;
  std::unique_ptr<Battle> currentBattle;
  BattleUI battleUI;
};

#endif

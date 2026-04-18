#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "battle.h"
#include "battleUI.h"
#include "constants.h"
#include "hero.h"
#include "infectedMonster.h"
#include "item.h"
#include "itemFactory.h"
#include "monster.h"
#include "monsterFactory.h"

struct Box {
  int x, y;
  bool active;
  Item loot;
};

struct MonsterInfo {
  Monster* ptr;
  int x, y;
  bool alive;
};

class Game {
 public:
  Game();
  ~Game();
  void run();

 private:
  void processInput();
  void update();
  void render();

  sf::RenderWindow window;
  int map[MAP_HEIGHT][MAP_WIDTH];
  int heroX, heroY;

  Hero hero;
  std::vector<MonsterInfo> monsters;
  std::vector<Box> boxes;

  bool inBattle;
  std::unique_ptr<Battle> currentBattle;
  BattleUI battleUI;

  MonsterFactory monsterFactory;
  ItemFactory itemFactory;
};

#endif

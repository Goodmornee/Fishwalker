#ifndef BATTLE_H
#define BATTLE_H

#include <vector>

#include "hero.h"
#include "monster.h"

class Battle {
 public:
  // конструктор
  Battle(Hero* hero, std::vector<Monster*> enemies);

  // функции
  void startBattle();
  bool isBattleOver() const;
  int countAliveEnemies() const;

  // деструктор
  ~Battle();

 private:
  Hero* hero;
  std::vector<Monster*> enemies;

  // функции
};

#endif  // BATTLE_H

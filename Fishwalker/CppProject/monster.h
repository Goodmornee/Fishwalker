#ifndef MONSTER_H
#define MONSTER_H

#include <string>

#include "character.h"

class Monster : public Character {
 public:
  // десруктор
  ~Monster();

  // конструктор
  Monster(const std::string& name, int id, int hp, int maxHp, int atk, int acc,
          int agl, int res, int inf, int crit);

  // функция
  void attack(Character& target) override;

  void update() override;
};

#endif  // MONSTER_H

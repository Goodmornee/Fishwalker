#ifndef HERO_H
#define HERO_H

#include <string>

#include "character.h"
#include "equipment.h"

class Hero : public Character {
 public:
  // конструктор
  Hero(const std::string& name, int id, int hp, int maxHp, int atk, int acc,
       int agl, int res, int inf, int crit, Equipment* currentWeapon = nullptr);

  // геттеры
  Equipment* getCurrentWeapon() const;

  // функци
  void attack(Character& target) override;

  void equip(Equipment* newWeapon);

  void update() override;

  // десруктор
  ~Hero();

 private:
  Equipment* currentWeapon;
};

#endif  // HERO_H

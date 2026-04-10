#include "hero.h"

#include <string>

// конструктор
Hero::Hero(const std::string& name, int id, int hp, int maxHp, int atk, int acc,
           int agl, int res, int inf, int crit, Equipment* currentWeapon)
    : Character(name, id, hp, maxHp, atk, acc, agl, res, inf, crit),
      currentWeapon(currentWeapon) {}

// геттеры
Equipment* Hero::getCurrentWeapon() const { return currentWeapon; }

// функции
void Hero::attack(Character& target) {
  int damage = getAtk() + (currentWeapon ? currentWeapon->getWeaponAtk() : 0);
  target.takeDamage(damage);
}

void Hero::equip(Equipment* newWeapon) { currentWeapon = newWeapon; }

void Hero::update() {}

// деструктор
Hero::~Hero() {}

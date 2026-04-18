#include "hero.h"

#include <string>

// конструктор
Hero::Hero(const std::string& name, int id, int hp, int maxHp, int atk, int acc,
           int agl, int res, int inf, int crit, Weapon* currentWeapon,
           Armor* currentArmor)
    : Character(name, id, hp, maxHp, atk, acc, agl, res, inf, crit),
      currentWeapon(currentWeapon),
      currentArmor(currentArmor) {}

// геттеры
Weapon* Hero::getCurrentWeapon() const { return currentWeapon; }
Inventory& Hero::getInventory() { return inventory; }
Armor* Hero::getCurrentArmor() { return currentArmor; }

// функции
void Hero::takeDamage(int amount) {
  int reduced = amount - (currentArmor ? currentArmor->getArmorDef() : 0);
  if (reduced < 0) reduced = 0;
  Character::takeDamage(reduced);
}
void Hero::attack(Character& target) {
  int damage = getAtk() + (currentWeapon ? currentWeapon->getWeaponAtk() : 0);
  target.takeDamage(damage);
}

void Hero::equipEquipment(Weapon* newWeapon) {
  if (currentWeapon != nullptr) delete currentWeapon;
  currentWeapon = newWeapon;
}
void Hero::equipArmor(Armor* newArmor) {
  if (currentArmor != nullptr) delete currentArmor;
  currentArmor = newArmor;
}

void Hero::update() {}

// деструктор
Hero::~Hero() {}

#include "weapon.h"

// конструктор
Weapon::Weapon(const std::string& weaponName, int weaponAtk, int weaponType)
    : weaponName(weaponName), weaponAtk(weaponAtk), weaponType(weaponType) {}

// реализация геттеров
const std::string& Weapon::getWeaponName() const { return weaponName; }
int Weapon::getWeaponAtk() const { return weaponAtk; }
int Weapon::getWeaponType() const { return weaponType; }

// реализациия сеттеров
void Weapon::setWeaponName(const std::string& newWeaponName) {
  weaponName = newWeaponName;
}
void Weapon::setWeaponAtk(int newWeaponAtk) { weaponAtk = newWeaponAtk; }
void Weapon::setWeaponType(int newWeaponType) { weaponType = newWeaponType; }

// деструктор
Weapon::~Weapon() {}

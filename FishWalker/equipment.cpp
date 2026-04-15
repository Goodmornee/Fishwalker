#include "equipment.h"

// конструктор
Equipment::Equipment(const std::string& weaponName, int weaponAtk,
                     int weaponType)
    : weaponName(weaponName), weaponAtk(weaponAtk), weaponType(weaponType) {}

// реализация геттеров
const std::string& Equipment::getWeaponName() const { return weaponName; }
int Equipment::getWeaponAtk() const { return weaponAtk; }
int Equipment::getWeaponType() const { return weaponType; }

// реализациия сеттеров
void Equipment::setWeaponName(const std::string& newWeaponName) {
  weaponName = newWeaponName;
}
void Equipment::setWeaponAtk(int newWeaponAtk) { weaponAtk = newWeaponAtk; }
void Equipment::setWeaponType(int newWeaponType) { weaponType = newWeaponType; }

// деструктор
Equipment::~Equipment() {}

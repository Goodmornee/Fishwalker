
#include "armor.h"

Armor::Armor(const std::string& armorName, int armorDef, int armorType)
    : armorName(armorName), armorDef(armorDef), armorType(armorType) {}

const std::string& Armor::getArmorName() const { return armorName; }
int Armor::getArmorDef() const { return armorDef; }
int Armor::getArmorType() const { return armorType; }

void Armor::setArmorName(const std::string& newArmorName) {
  armorName = newArmorName;
}
void Armor::setArmorDef(int newArmorDef) { armorDef = newArmorDef; }
void Armor::setArmorType(int newArmorType) { armorType = newArmorType; }

Armor::~Armor() {}

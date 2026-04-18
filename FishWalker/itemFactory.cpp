#include "itemFactory.h"

#include "constants.h"

Item ItemFactory::createHealthPotion() const {
  return Item("Health Potion", ItemType::HEAL, HEAL_POTION_AMOUNT);
}
Item ItemFactory::createAntidote() const {
  return Item("Antidote", ItemType::HEAL, ANTIDOTE_AMOUNT);
}
Item ItemFactory::createArmor() const {
  return Item("Leather Armor", ItemType::ARMOR, ARMOR_DEF);
}
Item ItemFactory::createWeapon() const {
  return Item("Knife", ItemType::WEAPON, WEAPON_DAMAGE);
}
Item ItemFactory::createItem() const {
  int r = rand() % 3;
  if (r == 0) return createHealthPotion();
  if (r == 1) return createArmor();
  return createWeapon();
}

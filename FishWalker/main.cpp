#include <SFML/Graphics.hpp>
#include <iostream>

#include "battle.h"
#include "equipment.h"
#include "hero.h"
#include "monster.h"

int main() {
  setlocale(LC_ALL, "rus");
  Hero hero("Рыбак", 1, 100, 100, 10, 50, 20, 10, 0, 5, nullptr);
  Monster monster("Фишвокер", 1, 20, 100, 10, 50, 20, 10, 0, 5);
  std::vector<Monster*> monsters;
  monsters.push_back(&monster);
  Battle battle(&hero, monsters);
  Equipment rod("Удочка", 15, 1);
  battle.startBattle();
  std::cout << "Оружие до экипировки: " << hero.getCurrentWeapon() << std::endl;
  hero.equip(&rod);
  std::cout << "Оружие после: " << hero.getCurrentWeapon()->getWeaponName()
            << std::endl;
  std::cout << "countAliveEnemies: " << battle.countAliveEnemies() << std::endl;

  return 0;
}

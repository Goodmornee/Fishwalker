#include "battle.h"

#include <iostream>

// конструктор
Battle::Battle(Hero* hero, std::vector<Monster*> enemies)
    : hero(hero), enemies(enemies) {}

// функции
void Battle::startBattle() {
  while (!isBattleOver()) {
    int aliveCount = countAliveEnemies();
    int actions = countAliveEnemies();
    for (int i = 0; i < actions && !isBattleOver(); ++i) {
      std::cout << "Герой: " << hero->getHp() << " HP\n";
      int choice;
      std::cout << "Живые враги:\n";
      for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->isAlive()) {
          std::cout << enemies[i]->getId() << ". " << enemies[i]->getName()
                    << "(" << enemies[i]->getHp() << "HP)\n";
        }
      }
      while (true) {
        std::cout << "Введите номер цели: ";
        if (std::cin >> choice) {
          if (choice >= 1 && choice <= aliveCount) {
            Monster* target = nullptr;
            for (size_t i = 0; i != choice; ++i) {
              if (enemies[i]->isAlive()) {
                hero->attack(*target);
                break;
              }
              choice = i;
              break;
            }
            hero->attack(*target);
            break;
          } else {
            std::cout << "Нет врага с таким номером.\n";
          }
        } else {
          std::cin.clear();
          std::cin.ignore(10000, '\n');
          std::cout << "Ошибка: нужно ввести число.\n";
        }
      }
    }
  }
}
bool Battle::isBattleOver() const {
  if (!hero->isAlive()) {
    return true;
  }
  for (size_t i = 0; i < enemies.size(); ++i) {
    if (enemies[i]->isAlive()) {
      return false;
    }
  }
  return true;
}
int Battle::countAliveEnemies() const {
  int cnt = 0;
  for (size_t i = 0; i < enemies.size(); ++i) {
    if (enemies[i]->isAlive()) {
      cnt++;
    }
  }
  return cnt;
}

// деструктор
Battle::~Battle() {}

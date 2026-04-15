#include "battle.h"

#include <iostream>

// конструктор
Battle::Battle(Hero* hero, std::vector<Monster*> enemies)
    : hero(hero), enemies(enemies) {}

// функции
void Battle::startBattle() {
  while (!isBattleOver()) {
    heroTurn();
    if (!isBattleOver()) {
      monstersTurn();
    }
    std::cout << "\n";
  }

  if (isBattleOver()) {
    if (hero->isAlive()) {
      std::cout << "Победа!\n";
    } else {
      std::cout << "Поражение\n";
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

void Battle::displayAliveEnemies() {
  int number = 1;
  for (size_t i = 0; i < enemies.size(); ++i) {
    if (enemies[i]->isAlive()) {
      std::cout << number << ". " << enemies[i]->getName() << "("
                << enemies[i]->getHp() << "HP)\n";
      ++number;
    }
  }
}

void Battle::monstersTurn() {
  for (auto* m : enemies) {
    if (m->isAlive()) {
      m->attack(*hero);
      if (!hero->isAlive()) break;
    }
  }
}

void Battle::heroTurn() {
  int actions = countAliveEnemies();
  for (int i = 0; i < actions && !isBattleOver(); ++i) {
    std::cout << hero->getName() << ": " << hero->getHp() << " HP\n";
    int choice;
    std::cout << "Живые враги:\n";
    displayAliveEnemies();
    while (true) {
      std::cout << "Введите номер цели: ";
      if (std::cin >> choice) {
        int aliveCount = countAliveEnemies();
        if (choice >= 1 && choice <= aliveCount) {
          Monster* target = nullptr;
          int live = 0;
          for (size_t i = 0; i < enemies.size(); ++i) {
            if (enemies[i]->isAlive()) {
              live++;
              if (live == choice) {
                target = enemies[i];
              }
            }
          }
          if (target != nullptr) {
            hero->attack(*target);
            if (!hero->isAlive()) break;
          }
          break;
        } else {
          std::cout << "Нет врага с таким номером\n";
        }
      } else {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Введите число\n";
      }
    }
  }
}

// деструктор
Battle::~Battle() {}

#include "game.h"

#include <iostream>

Game::Game()
    : window(sf::VideoMode({MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE}),
             "Fishwalker"),
      heroX(1),
      heroY(1),
      monsterX(5),
      monsterY(5),
      monsterAlive(true),
      hero("Fisherman", 1, 100, 100, 10, 50, 20, 10, 0, 5, nullptr),
      monster("Fishwalker", 1, 20, 100, 10, 50, 20, 10, 0, 5),
      inBattle(false),
      itemExists(true),
      itemX(3),
      itemY(3),
      currentItem("Fish", ItemType::HEAL, 20) {
  window.setFramerateLimit(60);

  // Заполняем карту полом (0)
  for (int y = 0; y < MAP_HEIGHT; ++y)
    for (int x = 0; x < MAP_WIDTH; ++x) map[y][x] = 0;

  // Стены по краям (1)
  for (int x = 0; x < MAP_WIDTH; ++x) {
    map[0][x] = 1;
    map[MAP_HEIGHT - 1][x] = 1;
  }
  for (int y = 0; y < MAP_HEIGHT; ++y) {
    map[y][0] = 1;
    map[y][MAP_WIDTH - 1] = 1;
  }
}

void Game::run() {
  while (window.isOpen()) {
    processInput();
    update();
    render();
  }
}

void Game::processInput() {
  while (const auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (inBattle) {
      // Передаём события в UI боя
      battleUI.handleEvent(*event);
    } else {
      // Обработка движения героя
      if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
        int newX = heroX, newY = heroY;
        if (key->scancode == sf::Keyboard::Scancode::Up) newY--;
        if (key->scancode == sf::Keyboard::Scancode::Down) newY++;
        if (key->scancode == sf::Keyboard::Scancode::Left) newX--;
        if (key->scancode == sf::Keyboard::Scancode::Right) newX++;

        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
            map[newY][newX] != 1) {
          // Проверка на монстра
          if (monsterAlive && newX == monsterX && newY == monsterY) {
            // Начинаем бой
            currentBattle = std::make_unique<Battle>(
                &hero, std::vector<Monster*>{&monster});
            battleUI.init(window, *currentBattle);
            inBattle = true;
          } else {
            heroX = newX;
            heroY = newY;
          }
        }
      }
    }
  }
}

void Game::update() {
  if (inBattle) {
    battleUI.update();
    if (battleUI.isFinished()) {
      inBattle = false;
      if (!hero.isAlive()) {
        // Герой умер – закрываем игру
        window.close();
      } else {
        // Монстр мёртв
        monsterAlive = false;
      }
      currentBattle.reset();
    }
  }
}

void Game::render() {
  window.clear();

  // Рисуем карту
  for (int y = 0; y < MAP_HEIGHT; ++y) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
      sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
      if (map[y][x] == 1)
        cell.setFillColor(sf::Color(100, 100, 100));
      else
        cell.setFillColor(sf::Color(200, 200, 200));
      window.draw(cell);
    }
  }

  // Рисуем монстра, если жив
  if (monsterAlive) {
    sf::RectangleShape monsterRect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    monsterRect.setFillColor(sf::Color::Red);
    monsterRect.setPosition(
        sf::Vector2f(monsterX * CELL_SIZE, monsterY * CELL_SIZE));
    window.draw(monsterRect);
  }

  // Рисуем героя
  sf::RectangleShape heroRect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  heroRect.setFillColor(sf::Color::Green);
  heroRect.setPosition(sf::Vector2f(heroX * CELL_SIZE, heroY * CELL_SIZE));
  window.draw(heroRect);

  // Если в бою – рисуем UI боя поверх
  if (inBattle) {
    battleUI.render(window);
  }

  window.display();
}

#include "game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game()
    : window(sf::VideoMode({MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE}),
             "Fishwalker"),
      heroX(1),
      heroY(1),
      hero("Fisherman", 1, HERO_START_HP, HERO_MAX_HP, HERO_ATK, HERO_ACC,
           HERO_AGL, HERO_RES, HERO_INF, HERO_CRIT, nullptr, nullptr),
      inBattle(false) {
  window.setFramerateLimit(60);
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  // Карта
  for (int y = 0; y < MAP_HEIGHT; ++y)
    for (int x = 0; x < MAP_WIDTH; ++x) map[y][x] = 0;
  for (int x = 0; x < MAP_WIDTH; ++x) {
    map[0][x] = 1;
    map[MAP_HEIGHT - 1][x] = 1;
  }
  for (int y = 0; y < MAP_HEIGHT; ++y) {
    map[y][0] = 1;
    map[y][MAP_WIDTH - 1] = 1;
  }

  // Монстры
  monsters.push_back({monsterFactory.createNormalMonster(), 5, 5, true});
  monsters.push_back({monsterFactory.createInfectedMonster(), 8, 8, true});

  // Отладка
  for (const auto& m : monsters) {
    std::cout << "Monster " << m.ptr->getName() << " HP = " << m.ptr->getHp()
              << std::endl;
  }

  // Сундуки
  boxes.push_back({3, 3, true, itemFactory.createItem()});
  boxes.push_back({10, 5, true, itemFactory.createItem()});
}

Game::~Game() {
  for (auto& m : monsters) {
    delete m.ptr;
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
      battleUI.handleEvent(*event);
    } else {
      if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
        int newX = heroX, newY = heroY;
        if (key->scancode == sf::Keyboard::Scancode::Up) newY--;
        if (key->scancode == sf::Keyboard::Scancode::Down) newY++;
        if (key->scancode == sf::Keyboard::Scancode::Left) newX--;
        if (key->scancode == sf::Keyboard::Scancode::Right) newX++;

        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
            map[newY][newX] != 1) {
          // Сундук
          for (auto& box : boxes) {
            if (box.active && newX == box.x && newY == box.y) {
              hero.getInventory().addItem(box.loot);
              std::cout << "Found a box! You got: " << box.loot.getName()
                        << std::endl;
              box.active = false;
              break;
            }
          }
          // Монстр
          bool monsterHere = false;
          for (auto& m : monsters) {
            if (m.alive && newX == m.x && newY == m.y) {
              std::cout << "Starting battle with " << m.ptr->getName()
                        << " HP=" << m.ptr->getHp() << std::endl;
              currentBattle =
                  std::make_unique<Battle>(&hero, std::vector<Monster*>{m.ptr});
              battleUI.init(window, *currentBattle);
              inBattle = true;
              monsterHere = true;
              break;
            }
          }
          if (!monsterHere) {
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
        window.close();
      } else {
        Monster* deadMonster = currentBattle->getMonsterPtr();
        for (auto& m : monsters) {
          if (m.ptr == deadMonster) {
            m.alive = false;
            delete m.ptr;
            m.ptr = nullptr;
            break;
          }
        }
      }
      currentBattle.reset();
    }
  }
}

void Game::render() {
  window.clear();

  // Карта
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

  // Сундуки
  for (const auto& box : boxes) {
    if (box.active) {
      sf::RectangleShape boxRect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      boxRect.setFillColor(sf::Color(160, 100, 50));
      boxRect.setPosition(sf::Vector2f(box.x * CELL_SIZE, box.y * CELL_SIZE));
      window.draw(boxRect);
    }
  }

  // Монстры
  for (const auto& m : monsters) {
    if (m.alive) {
      sf::RectangleShape monsterRect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      if (dynamic_cast<InfectedMonster*>(m.ptr))
        monsterRect.setFillColor(sf::Color(128, 0, 128));
      else
        monsterRect.setFillColor(sf::Color::Red);
      monsterRect.setPosition(sf::Vector2f(m.x * CELL_SIZE, m.y * CELL_SIZE));
      window.draw(monsterRect);
    }
  }

  // Герой
  sf::RectangleShape heroRect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  heroRect.setFillColor(sf::Color::Green);
  heroRect.setPosition(sf::Vector2f(heroX * CELL_SIZE, heroY * CELL_SIZE));
  window.draw(heroRect);

  // HUD
  static sf::Font hudFont;
  static bool hudFontLoaded = false;
  if (!hudFontLoaded) {
    hudFontLoaded = hudFont.openFromFile("arial.ttf");
  }
  if (hudFontLoaded) {
    sf::Text hudText(hudFont);
    hudText.setCharacterSize(20);
    hudText.setFillColor(sf::Color::White);
    hudText.setPosition(sf::Vector2f(10.f, 10.f));
    hudText.setString("HP: " + std::to_string(hero.getHp()) + "/" +
                      std::to_string(hero.getMaxHp()) +
                      "  INF: " + std::to_string(hero.getInf()) + "/100");
    window.draw(hudText);
  }

  if (inBattle) {
    battleUI.render(window);
  }

  window.display();
}

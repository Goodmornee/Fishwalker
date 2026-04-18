#include "battleUI.h"

#include <iostream>

static bool fontLoaded = false;
static sf::Font sharedFont;

BattleUI::BattleUI()
    : currentBattle(nullptr), battleFinished(false), showResult(false) {}

void BattleUI::init(sf::RenderWindow& window, Battle& battle) {
  currentBattle = &battle;
  battleFinished = false;
  showResult = false;

  // Загружаем шрифт только один раз
  if (!fontLoaded) {
    if (!sharedFont.openFromFile("arial.ttf")) {
      std::cerr << "Error: Cannot load arial.ttf in BattleUI" << std::endl;
      return;
    }
    fontLoaded = true;
  }

  // Создаём тексты (уникальные указатели, старые автоматически удалятся)
  heroHpText = std::make_unique<sf::Text>(sharedFont);
  heroHpText->setCharacterSize(24);
  heroHpText->setFillColor(sf::Color::White);
  heroHpText->setPosition(sf::Vector2f(50.f, 50.f));

  monsterHpText = std::make_unique<sf::Text>(sharedFont);
  monsterHpText->setCharacterSize(24);
  monsterHpText->setFillColor(sf::Color::White);
  monsterHpText->setPosition(sf::Vector2f(500.f, 50.f));

  actionMenuText = std::make_unique<sf::Text>(sharedFont);
  actionMenuText->setCharacterSize(20);
  actionMenuText->setFillColor(sf::Color::Yellow);
  actionMenuText->setString("1 - Attack\n2 - Item (not ready)");
  actionMenuText->setPosition(sf::Vector2f(300.f, 450.f));

  resultText = std::make_unique<sf::Text>(sharedFont);
  resultText->setCharacterSize(30);
  resultText->setFillColor(sf::Color::Red);
  resultText->setPosition(sf::Vector2f(300.f, 250.f));

  backgroundOverlay.setSize(
      sf::Vector2f(window.getSize().x, window.getSize().y));
  backgroundOverlay.setFillColor(sf::Color(0, 0, 0, 180));
}

void BattleUI::updateBarsAndText() {
  if (!currentBattle) return;

  Hero& hero = currentBattle->getHero();
  Monster& monster = currentBattle->getMonster();

  heroHpText->setString("Hero HP: " + std::to_string(hero.getHp()) + "/" +
                        std::to_string(hero.getMaxHp()));
  monsterHpText->setString("Monster HP: " + std::to_string(monster.getHp()) +
                           "/" + std::to_string(monster.getMaxHp()));

  float heroPercent = static_cast<float>(hero.getHp()) / hero.getMaxHp();
  float monsterPercent =
      static_cast<float>(monster.getHp()) / monster.getMaxHp();

  heroHpBar.setSize(sf::Vector2f(200.f * heroPercent, 20.f));
  heroHpBar.setFillColor(sf::Color::Green);
  heroHpBar.setPosition(sf::Vector2f(50.f, 80.f));

  monsterHpBar.setSize(sf::Vector2f(200.f * monsterPercent, 20.f));
  monsterHpBar.setFillColor(sf::Color::Red);
  monsterHpBar.setPosition(sf::Vector2f(500.f, 80.f));
}

void BattleUI::handleEvent(const sf::Event& event) {
  if (battleFinished) {
    if (event.is<sf::Event::KeyPressed>()) {
      battleFinished = false;
      showResult = false;
    }
    return;
  }

  if (event.is<sf::Event::KeyPressed>()) {
    const auto* key = event.getIf<sf::Event::KeyPressed>();
    if (key->scancode == sf::Keyboard::Scancode::Num1) {
      currentBattle->heroAttack();
      updateBarsAndText();
      if (currentBattle->isBattleOver()) {
        showResult = true;
        if (currentBattle->isHeroAlive())
          resultText->setString("VICTORY!\nPress any key");
        else
          resultText->setString("DEFEAT...\nPress any key");
        battleFinished = true;
      }
    }
  }
}

void BattleUI::update() {
  if (!currentBattle) return;
  updateBarsAndText();
}

void BattleUI::render(sf::RenderWindow& window) {
  window.draw(backgroundOverlay);
  if (heroHpText) window.draw(*heroHpText);
  if (monsterHpText) window.draw(*monsterHpText);
  window.draw(heroHpBar);
  window.draw(monsterHpBar);
  if (actionMenuText) window.draw(*actionMenuText);
  if (showResult && resultText) window.draw(*resultText);
}

bool BattleUI::isFinished() const { return battleFinished; }

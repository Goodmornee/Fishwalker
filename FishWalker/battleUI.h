#ifndef BATTLEUI_H
#define BATTLEUI_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "battle.h"

class BattleUI {
 public:
  BattleUI();
  void init(sf::RenderWindow& window, Battle& battle);
  void handleEvent(const sf::Event& event);
  void update();
  void render(sf::RenderWindow& window);
  bool isFinished() const;

 private:
  Battle* currentBattle;
  sf::Font font;
  std::unique_ptr<sf::Text> heroHpText;
  std::unique_ptr<sf::Text> monsterHpText;
  std::unique_ptr<sf::Text> actionMenuText;
  std::unique_ptr<sf::Text> resultText;
  sf::RectangleShape heroHpBar;
  sf::RectangleShape monsterHpBar;
  sf::RectangleShape backgroundOverlay;
  bool battleFinished;
  bool showResult;
  void updateBarsAndText();
};

#endif

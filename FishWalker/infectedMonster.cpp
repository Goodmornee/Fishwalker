#include "infectedMonster.h"

InfectedMonster::InfectedMonster(const std::string& name, int id, int hp,
                                 int maxHp, int atk, int acc, int agl, int res,
                                 int inf, int crit, int infectionPower)
    : Monster(name, id, hp, maxHp, atk, acc, agl, res, inf, crit),
      infectionPower(infectionPower) {}

InfectedMonster::~InfectedMonster() {}

void InfectedMonster::attack(Character& target) {
  target.takeDamage(getAtk());
  target.takeInfection(infectionPower);
}

void InfectedMonster::update() {}

int InfectedMonster::getInfectionPower() const { return infectionPower; }

#include "character.h"

// конструктор
Character::Character(const std::string& name, int id, int hp, int maxHp,
                     int atk, int acc, int agl, int res, int inf, int crit)
    : Entity(name, id),
      hp(hp),
      maxHp(maxHp),
      atk(atk),
      acc(acc),
      agl(agl),
      res(res),
      inf(inf),
      crit(crit) {}

// релизация функций
bool Character::isAlive() const { return hp > 0; }
void Character::takeDamage(int amount_damage) { setHp(hp - amount_damage); }
void Character::heal(int amount_hp) { setHp(hp + amount_hp); }
void Character::takeInfection(int amount_infection) {
  setInf(inf + amount_infection);
}

// реализация геттеров
int Character::getHp() const { return hp; }
int Character::getMaxHp() const { return maxHp; }
int Character::getAtk() const { return atk; }
int Character::getAcc() const { return acc; }
int Character::getAgl() const { return agl; }
int Character::getRes() const { return res; }
int Character::getInf() const { return inf; }
int Character::getCrit() const { return crit; }

// реализациия сеттеров
void Character::setHp(int newHp) {
  if (newHp <= 0) {
    newHp = 0;
  }
  if (newHp > maxHp) {
    newHp = maxHp;
  }
  hp = newHp;
  if (hp == 0) {
    // СДЕЛАТЬ СМЕРТЬ
  }
}
void Character::setMaxHp(int newMaxHp) {
  if (newMaxHp <= 0) {
    newMaxHp = 1;
  }
  maxHp = newMaxHp;
  if (hp > maxHp) {
    hp = maxHp;
  }
}
void Character::setAtk(int newAtk) {
  if (newAtk < 0) {
    newAtk = 0;
  }
  atk = newAtk;
}
void Character::setAcc(int newAcc) {
  if (newAcc < 0) {
    newAcc = 0;
  }
  if (newAcc > 100) {
    newAcc = 100;
  }
  acc = newAcc;
}
void Character::setAgl(int newAgl) {
  if (newAgl < 0) {
    newAgl = 0;
  }
  if (newAgl > 100) {
    newAgl = 100;
  }
  agl = newAgl;
}
void Character::setRes(int newRes) {
  if (newRes < 0) {
    newRes = 0;
  }
  if (newRes > 100) {
    newRes = 100;
  }
  res = newRes;
}
void Character::setInf(int newInf) {
  if (newInf < 0) {
    newInf = 0;
  }
  if (newInf > 100) {
    newInf = 100;
  }
  inf = newInf;
  if (inf >= 70) {
    // СДЕЛАТЬ ПОБОЧКИ
  }
  if (inf == 100) {
    // СДЕЛАТЬ СМЕРТЬ
  }
}
void Character::setCrit(int newCrit) {
  if (newCrit < 0) {
    newCrit = 0;
  }
  if (newCrit > 100) {
    newCrit = 100;
  }
  crit = newCrit;
}

// деструктор
Character::~Character() {}

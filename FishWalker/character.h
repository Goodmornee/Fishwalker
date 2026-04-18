#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include "entity.h"

class Character : public Entity {
 public:
  // десруктор
  ~Character();

  // конструктор
  Character(const std::string& name, int id, int hp, int maxHp, int atk,
            int acc, int agl, int res, int inf, int crit);

  // геттеры
  int getHp() const;
  int getMaxHp() const;
  int getAtk() const;
  int getAcc() const;
  int getAgl() const;
  int getRes() const;
  int getInf() const;
  int getCrit() const;

  // функции
  bool isAlive() const;
  virtual void takeDamage(int amount_damage);
  void heal(int amount_hp);
  void takeInfection(int amount_infection);

  // виртуальная функция
  virtual void attack(Character& target) = 0;

 protected:
  // поля
  int hp, maxHp, atk, acc, agl, res, inf, crit;

  // сеттеры
  void setHp(int newHp);
  void setMaxHp(int newMaxHp);
  void setAtk(int newAtk);
  void setAcc(int newAcc);
  void setAgl(int newAgl);
  void setRes(int newRes);
  void setInf(int newInf);
  void setCrit(int newCrit);
};

#endif  // CHARACTER_H

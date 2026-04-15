#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
 public:
  // виртуальный деструктор
  virtual ~Entity();

  // конструктор
  Entity(const std::string& name, int id);

  // виртуальная функция
  virtual void update() = 0;

  // геттеры
  int getId() const;
  const std::string& getName() const;

 protected:
  // поля
  std::string name;
  int id;
};

#endif  // ENTITY_H

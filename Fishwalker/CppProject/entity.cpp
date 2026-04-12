#include "entity.h"

// конструктор
Entity::Entity(const std::string& name, int id) : id(id), name(name) {}

// реализация геттеров
int Entity::getId() const { return id; }
const std::string& Entity::getName() const { return name; }

// деструктор
Entity::~Entity() {}

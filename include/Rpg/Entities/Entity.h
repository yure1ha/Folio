#pragma once

#include "Rpg/Components/IdComponent.h"

namespace Rpg {

class Entity {
  public:
    explicit Entity(IdComponent id) : m_id {id} {}

    virtual ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Entity(Entity&&) = delete;
    Entity& operator=(Entity&&) = delete;

    IdComponent& id() {
        return m_id;
    }

    IdComponent id() const {
        return m_id;
    }

  private:
    IdComponent m_id;
};

} // namespace Rpg

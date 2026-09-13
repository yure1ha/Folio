#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Core/Types.h"

#include <memory>

namespace Rpg {

class Entity {
public:
  explicit Entity(IdComponent id) : m_id {id} {}

  virtual ~Entity() = default;

  Entity(const Entity&) = delete;
  Entity& operator=(const Entity&) = delete;

  Entity(Entity&&) = delete;
  Entity& operator=(Entity&&) = delete;

  IdComponent id() const {
    return m_id;
  }

  void setInstanceId(InstanceId id) {
    m_id.instanceId = id;
  }

private:
  IdComponent m_id;
};

using EntityUPtr = std::unique_ptr<Entity>;

} // namespace Rpg

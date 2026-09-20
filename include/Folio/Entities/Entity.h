#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Entities/EntityType.h"

#include <memory>

namespace Folio {

class Entity {
public:
  explicit Entity(IdComponent id) : m_id {id} {}

  virtual ~Entity() = default;

  Entity(const Entity&) = delete;
  Entity& operator=(const Entity&) = delete;

  Entity(Entity&&) noexcept = delete;
  Entity& operator=(Entity&&) noexcept = delete;

  virtual EntityType type() const { return EntityType::None; }

  IdComponent id() const { return m_id; }
  void setInstanceId(InstanceId id) { m_id.instanceId = id; }

private:
  IdComponent m_id;
};

using EntityUPtr = std::unique_ptr<Entity>;

} // namespace Folio

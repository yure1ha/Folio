#pragma once

#include "Rpg/Components/IdComponent.h"

namespace Rpg
{

class Entity
{
public:
  Entity() = default;

  explicit Entity(IdComponent id) : m_id {id}
  {
  }

  IdComponent& id()      { return m_id; }
  IdComponent id() const { return m_id; }

protected:
  IdComponent m_id;
};

} // namespace Rpg

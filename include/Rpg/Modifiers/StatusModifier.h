#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Modifiers/StatusModifierType.h"
#include "Rpg/Components/StackComponent.h"

#include <cstdint>
#include <optional>

namespace Rpg
{

struct StatusModifier
{
  IdComponent id;
  StatusModifierType type {};
  StackComponent stack;
  std::int32_t value {};

  std::int32_t sortKey() const { return value; }
  std::int32_t total() const { return value * stack.current(); }
  bool isActive() const { return stack.current() > 0; }
};

} // namespace Rpg

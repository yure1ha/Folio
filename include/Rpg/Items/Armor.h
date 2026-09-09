#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Modifiers/StatusModifier.h"

#include <cstdint>

namespace Rpg
{

struct Armor
{
  IdComponent id;
  StackComponent stack;
  DefenseComponent defense;
  StatusModifier modifier;

  std::int32_t sortKey() const { return defense.effective(); }
};

} // namespace Rpg

#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Modifiers/StatusModifier.h"

#include <cstdint>

namespace Rpg
{

struct Weapon
{
  IdComponent id;
  StackComponent stack;
  StrengthComponent strength;
  StatusModifier modifier;

  std::int32_t sortKey() const { return strength.effective(); }
};

} // namespace Rpg

#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Modifiers/StatusModifier.h"

namespace Rpg {

struct Weapon {
  IdComponent id;
  StackComponent stack;
  StrengthComponent strength;
  StatusModifier modifier;

  Strength sortKey() const {
    return strength.effective();
  }
};

} // namespace Rpg

#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Modifiers/StatusModifierType.h"

namespace Rpg {

struct Weapon {
  IdComponent id;
  StackComponent stack;
  StrengthComponent strength;
  StatusModifier modifier;

  Strength sortKey() const {
    return strength.effective();
  }

  bool hasStatusModifier() const {
    return modifier.type != StatusModifierType::None;
  }
};

} // namespace Rpg

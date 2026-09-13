#pragma once

#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Modifiers/StatusModifierType.h"

namespace Rpg {

struct Armor {
  IdComponent id;
  StackComponent stack;
  DefenseComponent defense;
  StatusModifier modifier;

  Defense sortKey() const {
    return defense.effective();
  }

  bool hasStatusModifier() const {
    return modifier.type != StatusModifierType::None;
  }
};

} // namespace Rpg

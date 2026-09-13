#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Modifiers/InstantModifier.h"
#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Modifiers/StatusModifierType.h"
#include "Rpg/Modifiers/InstantModifierType.h"

namespace Rpg {

struct Consumable {
  IdComponent id;
  StackComponent stack;
  StatusModifier statusModifier;
  InstantModifier instantModifier;

  Stack sortKey() const {
    return stack.current();
  }

  bool hasStatusModifier() const {
    return statusModifier.type != StatusModifierType::None;
  }

  bool hasInstantModifier() const {
    return instantModifier.type != InstantModifierType::None;
  }
};

} // namespace Rpg

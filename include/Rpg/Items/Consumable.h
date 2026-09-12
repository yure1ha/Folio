#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Modifiers/StatusModifier.h"

namespace Rpg {

struct Consumable {
  IdComponent id;
  StackComponent stack;
  StatusModifier modifier;

  Stack sortKey() const {
    return stack.current();
  }
};

} // namespace Rpg

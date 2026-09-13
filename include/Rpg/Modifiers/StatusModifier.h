#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Modifiers/StatusModifierType.h"

namespace Rpg {

struct StatusModifier {
  IdComponent id;
  StatusModifierType type {};
  StackComponent stack;
  Modifier value {};

  Modifier sortKey() const {
    return value;
  }

  bool active() const {
    return stack.current() > 0;
  }

  Modifier total() const {
    return value * stack.current();
  }
};

} // namespace Rpg

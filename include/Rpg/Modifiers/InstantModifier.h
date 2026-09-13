#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Modifiers/InstantModifierType.h"

namespace Rpg {

struct InstantModifier {
  IdComponent id;
  InstantModifierType type {};
  Modifier value {};
};

} // namespace Rpg

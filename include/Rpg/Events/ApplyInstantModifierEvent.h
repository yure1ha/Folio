#pragma once

#include "Rpg/Systems/EventManager.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Modifiers/InstantModifier.h"

namespace Rpg {

struct ApplyInstantModifierEvent {
  InstantModifier modifier;
  IdComponent targetId;
};

using ApplyInstantModifierEventManager = EventManager<ApplyInstantModifierEvent>;

} // namespace Rpg

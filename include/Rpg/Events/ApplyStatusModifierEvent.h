#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Events/EventManager.h"
#include "Rpg/Modifiers/StatusModifier.h"

namespace Rpg {

struct ApplyStatusModifierEvent {
  StatusModifier modifier;
  IdComponent targetId;
};

using ApplyStatusModifierEventManager = EventManager<ApplyStatusModifierEvent>;

} // namespace Rpg

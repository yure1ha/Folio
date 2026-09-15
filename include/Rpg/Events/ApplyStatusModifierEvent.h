#pragma once

#include "Rpg/Systems/EventManager.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Modifiers/StatusModifier.h"

namespace Rpg {

struct ApplyStatusModifierEvent {
  StatusModifier modifier;
  IdComponent sourceId;
  IdComponent targetId;
};

using ApplyStatusModifierEventManager = EventManager<ApplyStatusModifierEvent>;

} // namespace Rpg

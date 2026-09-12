#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Events/EventManager.h"

namespace Rpg {

struct RemoveStatusModifierEvent {
  IdComponent modifierId;
  IdComponent targetId;
};

using RemoveStatusModifierEventManager = EventManager<RemoveStatusModifierEvent>;

} // namespace Rpg

#pragma once

#include "Rpg/Systems/EventManager.h"
#include "Rpg/Components/IdComponent.h"

namespace Rpg {

struct RemoveStatusModifierEvent {
  IdComponent modifierId;
  IdComponent targetId;
};

using RemoveStatusModifierEventManager = EventManager<RemoveStatusModifierEvent>;

} // namespace Rpg

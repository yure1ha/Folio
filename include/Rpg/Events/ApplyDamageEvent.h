#pragma once

#include "Rpg/Systems/EventManager.h"
#include "Rpg/Components/IdComponent.h"

namespace Rpg {

struct ApplyDamageEvent {
  IdComponent sourceId;
  IdComponent targetId;
};

using DamageEventManager = EventManager<ApplyDamageEvent>;

} // namespace Rpg

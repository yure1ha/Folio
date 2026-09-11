#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Events/EventManager.h"

namespace Rpg {

struct ApplyDamageEvent {
    InstanceId sourceId {};
    InstanceId targetId {};
};

using DamageEventManager = EventManager<ApplyDamageEvent>;

} // namespace Rpg

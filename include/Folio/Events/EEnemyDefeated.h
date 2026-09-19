#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Systems/EventManager.h"

namespace Folio {

struct EEnemyDefeated {
  IdComponent sourceId;
  IdComponent targetId;
  Experience exp {};
};

using EEnemyDefeatedManager = EventManager<EEnemyDefeated>;

} // namespace Folio

#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Systems/EventManager.h"

namespace Folio {

struct ECharacterDefeated {
  IdComponent sourceId;
  IdComponent targetId;
};

using ECharacterDefeatedManager = EventManager<ECharacterDefeated>;

} // namespace Folio

#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Systems/EventManager.h"

namespace Folio {

struct EApplyDamage {
  IdComponent sourceId;
  IdComponent targetId;
};

using EApplyDamageManager = EventManager<EApplyDamage>;

} // namespace Folio

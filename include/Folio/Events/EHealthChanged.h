#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Systems/EventManager.h"

namespace Folio {

struct EHealthChanged {
  IdComponent sourceId;
  IdComponent targetId;
};

using EHealthChangedManager = EventManager<EHealthChanged>;

} // namespace Folio

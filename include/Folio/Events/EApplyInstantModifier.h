#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Modifiers/InstantModifier.h"
#include "Folio/Systems/EventManager.h"

namespace Folio {

struct EApplyInstantModifier {
  InstantModifier modifier;
  IdComponent sourceId;
  IdComponent targetId;
};

using EApplyInstantModifierManager = EventManager<EApplyInstantModifier>;

} // namespace Folio

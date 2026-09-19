#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Modifiers/StatusModifier.h"
#include "Folio/Systems/EventManager.h"

namespace Folio {

struct EApplyStatusModifier {
  StatusModifier modifier;
  IdComponent sourceId;
  IdComponent targetId;
};

using EApplyStatusModifierManager = EventManager<EApplyStatusModifier>;

} // namespace Folio

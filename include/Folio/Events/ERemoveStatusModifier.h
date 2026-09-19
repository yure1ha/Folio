#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Systems/EventManager.h"

namespace Folio {

struct ERemoveStatusModifier {
  IdComponent modifierId;
  IdComponent targetId;
};

using ERemoveStatusModifierManager = EventManager<ERemoveStatusModifier>;

} // namespace Folio

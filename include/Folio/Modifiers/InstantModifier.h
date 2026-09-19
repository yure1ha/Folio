#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Modifiers/InstantModifierType.h"

namespace Folio {

struct InstantModifier {
  IdComponent id;
  InstantModifierType type {};
  Modifier value {};
};

} // namespace Folio

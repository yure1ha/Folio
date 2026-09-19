#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StackComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Modifiers/InstantModifier.h"
#include "Folio/Modifiers/InstantModifierType.h"
#include "Folio/Modifiers/StatusModifier.h"
#include "Folio/Modifiers/StatusModifierType.h"

namespace Folio {

struct Consumable {
  IdComponent id;
  StackComponent stack;
  StatusModifier statusModifier;
  InstantModifier instantModifier;

  Stack sortKey() const { return stack.current(); }

  bool hasStatusModifier() const { return statusModifier.type != StatusModifierType::None; }

  bool hasInstantModifier() const { return instantModifier.type != InstantModifierType::None; }
};

} // namespace Folio

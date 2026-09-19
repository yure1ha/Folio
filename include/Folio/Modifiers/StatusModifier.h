#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StackComponent.h"
#include "Folio/Components/ValueComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Modifiers/StatusModifierType.h"

namespace Folio {

struct StatusModifier {
  IdComponent id;
  StatusModifierType type {};
  StackComponent stack;
  ValueComponent value {};
  TurnDuration duration {};

  Modifier sortKey() const { return value.total(); }

  bool active() const { return stack.current() > 0 || duration > 0; }

  Modifier total() const { return value.total() * stack.current(); }
};

} // namespace Folio

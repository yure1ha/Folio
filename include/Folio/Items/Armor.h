#pragma once

#include "Folio/Components/DefenseComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StackComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Modifiers/StatusModifier.h"
#include "Folio/Modifiers/StatusModifierType.h"

namespace Folio {

struct Armor {
  IdComponent id;
  StackComponent stack;
  DefenseComponent defense;
  StatusModifier modifier;

  Defense sortKey() const { return defense.effective(); }

  bool hasStatusModifier() const { return modifier.type != StatusModifierType::None; }
};

} // namespace Folio

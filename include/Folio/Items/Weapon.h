#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StackComponent.h"
#include "Folio/Components/StrengthComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Modifiers/StatusModifier.h"
#include "Folio/Modifiers/StatusModifierType.h"

namespace Folio {

struct Weapon {
  IdComponent id;
  StackComponent stack;
  StrengthComponent strength;
  StatusModifier modifier;

  Strength sortKey() const { return strength.effective(); }

  bool hasStatusModifier() const { return modifier.type != StatusModifierType::None; }
};

} // namespace Folio

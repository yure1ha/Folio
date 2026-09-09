#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Concepts/AttributeComponent.h"

namespace Rpg::StatusModifierSystem
{

using StatusModifierList = ContainerComponent<StatusModifier>;

void addModifier(const StatusModifier& modifier,
                 StatusModifierList& modifierList);

void removeModifier(const StatusModifier& modifier,
                    StatusModifierList& modifierList);

template <Concepts::AttributeComponent T>
void applyModifier(const StatusModifier& modifier, T& attr)
{
  if (!modifier.isActive() || modifier.type != T::kModifierType) return;

  if (const auto total {modifier.total()}; total > 0)
  {
    attr.increase(total);
  }

  else if (total < 0)
  {
    attr.decrease(-total);
  }
}

template <Concepts::AttributeComponent T>
void updateModifiers(const StatusModifierList& modifierList, T& attr)
{
  for (const auto& modifier: modifierList)
  {
    applyModifier(modifier, attr);
  }
}

} // namespace Rpg::StatusModifierSystem

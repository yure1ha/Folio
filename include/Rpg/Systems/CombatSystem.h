#pragma once

#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Components/DefenseComponent.h"

namespace Rpg::CombatSystem
{

std::int32_t calculateDamage(const StrengthComponent& str,
                             const DefenseComponent& def);

template <typename T, typename U>
void applyDamage(const T& source, U& target)
{
  const auto amount {calculateDamage(source.strength, target.defense)};
  target.health.takeDamage(amount);
}

} // namespace Rpg::CombatSystem

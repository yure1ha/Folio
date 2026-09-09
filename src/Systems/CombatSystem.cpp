#include "Rpg/Systems/CombatSystem.h"

#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Components/DefenseComponent.h"

#include <cstdint>

namespace Rpg::CombatSystem
{

std::int32_t calculateDamage(const StrengthComponent& str, const DefenseComponent& def)
{
  return str.effective() - def.effective();
}

} // namespace Rpg::CombatSystem

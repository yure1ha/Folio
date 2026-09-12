#pragma once

#include "Rpg/Core/Types.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Modifiers/StatusModifier.h"

#include <optional>
#include <vector>

namespace Rpg {

struct EnemyBlueprint {
  TypeId typeId {};

  Health baseHealth {};
  Health effectiveHealth {};
  Health currentHealth {};

  Strength baseStrength {};
  Strength effectiveStrength {};

  Defense baseDefense {};
  Defense effectiveDefense {};

  std::optional<Weapon> equippedWeapon {};
  std::optional<Armor> equippedArmor {};

  std::vector<StatusModifier> modifiers {};
};

} // namespace Rpg

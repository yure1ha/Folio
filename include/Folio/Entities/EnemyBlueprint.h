#pragma once

#include "Folio/Core/Types.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Weapon.h"
#include "Folio/Modifiers/StatusModifier.h"

#include <optional>
#include <vector>

namespace Folio {

struct EnemyBlueprint {
  TypeId typeId {};
  Experience baseExp {};

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

} // namespace Folio

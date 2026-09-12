#pragma once

#include "Rpg/Core/Types.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Modifiers/StatusModifier.h"

#include <optional>
#include <vector>

namespace Rpg {

struct CharacterBlueprint {
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

  std::vector<Consumable> consumables {};
  std::vector<Weapon> weapons {};
  std::vector<Armor> armor {};
  std::vector<StatusModifier> modifiers {};
};

} // namespace Rpg

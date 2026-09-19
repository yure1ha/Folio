#pragma once

#include "Folio/Core/Types.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Consumable.h"
#include "Folio/Items/Weapon.h"
#include "Folio/Modifiers/StatusModifier.h"

#include <optional>
#include <vector>

namespace Folio {

struct CharacterBlueprint {
  TypeId typeId {};
  Level level {};
  Experience currentExp {};

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

} // namespace Folio

#pragma once

#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Modifiers/StatusModifier.h"

#include <cstdint>
#include <optional>
#include <vector>

namespace Rpg
{

struct CharacterBlueprint
{
  std::int32_t typeId {};

  std::int32_t baseHealth {};
  std::int32_t effectiveHealth {};
  std::int32_t currentHealth {};

  std::int32_t baseStrength {};
  std::int32_t effectiveStrength {};

  std::int32_t baseDefense {};
  std::int32_t effectiveDefense {};

  std::optional<Weapon> equippedWeapon {};
  std::optional<Armor> equippedArmor {};

  std::vector<Consumable> consumables {};
  std::vector<Weapon> weapons {};
  std::vector<Armor> armor {};
  std::vector<StatusModifier> modifiers {};
};

} // namespace Rpg

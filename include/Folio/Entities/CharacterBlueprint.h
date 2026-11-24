#pragma once

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Components/Containers.h"
#include "Folio/Components/EquipmentComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Weapon.h"

#include <optional>

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

  EquippedWeapon equippedWeapon {};
  EquippedArmor equippedArmor {};

  ConsumableInventory consumables {};
  WeaponInventory weapons {};
  ArmorInventory armor {};
  StatusModifierList modifiers {};
};

} // namespace Folio

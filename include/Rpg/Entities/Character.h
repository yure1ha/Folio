#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/EquipmentComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Entities/CharacterBlueprint.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"

namespace Rpg {

class Character : public Combatant {
public:
  using ConsumableInventory = ContainerComponent<Consumable>;
  using WeaponInventory = ContainerComponent<Weapon>;
  using ArmorInventory = ContainerComponent<Armor>;

  explicit Character(const CharacterBlueprint& bp);

  const EquipmentComponent& equipment() const {
    return m_equipment;
  }

  const ConsumableInventory& consumables() const {
    return m_consumables;
  }

  const WeaponInventory& weapons() const {
    return m_weapons;
  }

  const ArmorInventory& armor() const {
    return m_armor;
  }

  void useConsumable(IdComponent consumableId);
  void unequipWeapon();
  void unequipArmor();
  void equipWeapon(IdComponent weaponId);
  void equipArmor(IdComponent armorId);

private:
  EquipmentComponent m_equipment;
  ConsumableInventory m_consumables;
  WeaponInventory m_weapons;
  ArmorInventory m_armor;
};

} // namespace Rpg

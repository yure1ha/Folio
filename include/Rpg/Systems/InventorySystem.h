#pragma once

#include "EntityManager.h"
#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Concepts/ContainerItem.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Systems/ModifierSystem.h"
#include "Rpg/Systems/SystemType.h"

namespace Rpg {

class InventorySystem {
public:
  using ConsumableInventory = ContainerComponent<Consumable>;
  using WeaponInventory = ContainerComponent<Weapon>;
  using ArmorInventory = ContainerComponent<Armor>;

  InventorySystem(EntityManager& entityManager, ModifierSystem& modifierSystem);

  static constexpr SystemType type() {
    return SystemType::Inventory;
  }

  template <Concepts::ContainerItem T>
  static void addItem(const T& item, ContainerComponent<T>& inventory) {
    inventory.add(item);
  }

  template <Concepts::ContainerItem T>
  static void removeItem(const T& item, ContainerComponent<T>& inventory) {
    inventory.remove(item.id);
  }

  void useConsumable(IdComponent consumableId, IdComponent sourceId, IdComponent targetId) const;
  void unequipWeapon(IdComponent targetId) const;
  void unequipArmor(IdComponent targetId) const;
  void equipWeapon(IdComponent weaponId, IdComponent targetId) const;
  void equipArmor(IdComponent armorId, IdComponent targetId) const;

private:
  EntityManager& m_entityManager;
  ModifierSystem& m_modifierSystem;
};

} // namespace Rpg

#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Concepts/ContainerItem.h"
#include "Rpg/Entities/EntityManager.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Systems/StatusModifierSystem.h"
#include "Rpg/Systems/SystemType.h"

namespace Rpg {

class InventorySystem {
public:
  using ConsumableInventory = ContainerComponent<Consumable>;
  using WeaponInventory = ContainerComponent<Weapon>;
  using ArmorInventory = ContainerComponent<Armor>;

  InventorySystem(EntityManager& entityManager, StatusModifierSystem& modifierSystem);

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

  void useConsumable(const Consumable& consumable, IdComponent targetId) const;
  void unequipWeapon(IdComponent targetId) const;
  void unequipArmor(IdComponent targetId) const;
  void equipWeapon(const Weapon& weapon, IdComponent targetId) const;
  void equipArmor(const Armor& armor, IdComponent targetId) const;

private:
  EntityManager& m_entityManager;
  StatusModifierSystem& m_modifierSystem;
};

} // namespace Rpg

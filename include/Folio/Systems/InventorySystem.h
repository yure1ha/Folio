#pragma once

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Concepts/ContainerItem.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Consumable.h"
#include "Folio/Items/Weapon.h"
#include "Folio/Systems/EntityManager.h"
#include "Folio/Systems/ModifierSystem.h"
#include "Folio/Systems/SystemType.h"

namespace Folio {

class InventorySystem {
public:
  using ConsumableInventory = ContainerComponent<Consumable>;
  using WeaponInventory = ContainerComponent<Weapon>;
  using ArmorInventory = ContainerComponent<Armor>;

  InventorySystem(EntityManager& entityManager, ModifierSystem& modifierSystem);

  static constexpr SystemType type() { return SystemType::Inventory; }

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

} // namespace Folio

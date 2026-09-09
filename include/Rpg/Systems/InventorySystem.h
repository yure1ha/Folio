#pragma once

#include "Rpg/Concepts/ContainerItem.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/EquipmentComponent.h"

namespace Rpg::InventorySystem
{

using ConsumableInventory = ContainerComponent<Consumable>;
using WeaponInventory     = ContainerComponent<Weapon>;
using ArmorInventory      = ContainerComponent<Armor>;

template <Concepts::ContainerItem T>
void addItem(const T& item, ContainerComponent<T>& inventory)
{
  inventory.add(item);
}

template <Concepts::ContainerItem T>
void removeItem(const T& item, ContainerComponent<T>& inventory)
{
  inventory.remove(item.id);
}

void useConsumable(const Consumable& consumable,
                   ConsumableInventory& inventory);

void unequipWeapon(EquipmentComponent& equipment,
                   WeaponInventory& weaponInventory);

void unequipArmor(EquipmentComponent& equipment,
                  ArmorInventory& armorInventory);

void equipWeapon(const Weapon& weapon, EquipmentComponent& equipment,
                 WeaponInventory& weaponInventory);

void equipArmor(const Armor& armor, EquipmentComponent& equipment,
                ArmorInventory& armorInventory);

} // namespace Rpg::InventorySystem

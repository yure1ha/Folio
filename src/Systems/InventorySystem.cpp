#include "Rpg/Systems/InventorySystem.h"

#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Components/EquipmentComponent.h"

namespace Rpg::InventorySystem
{

void useConsumable(const Consumable& consumable,
                   ConsumableInventory& inventory)
{
  if (!inventory.contains(consumable.id)) return;

  inventory.remove(consumable.id);
}

void unequipWeapon(EquipmentComponent& equipment,
                   WeaponInventory& weaponInventory)
{
  if (!equipment.weapon.has_value()) return;

  weaponInventory.add(*equipment.weapon);
  equipment.weapon.reset();
}

void unequipArmor(EquipmentComponent& equipment,
                  ArmorInventory& armorInventory)
{
  if (!equipment.armor.has_value()) return;

  armorInventory.add(*equipment.armor);
  equipment.armor.reset();
}

void equipWeapon(const Weapon& weapon, EquipmentComponent& equipment,
                 WeaponInventory& weaponInventory)
{
  if (!weaponInventory.contains(weapon.id)) return;

  unequipWeapon(equipment, weaponInventory);
  weaponInventory.remove(weapon.id);
  equipment.weapon = weapon;
}

void equipArmor(const Armor& armor, EquipmentComponent& equipment,
                ArmorInventory& armorInventory)
{
  if (!armorInventory.contains(armor.id)) return;

  unequipArmor(equipment, armorInventory);
  armorInventory.remove(armor.id);
  equipment.armor = armor;
}

} // namespace Rpg::InventorySystem

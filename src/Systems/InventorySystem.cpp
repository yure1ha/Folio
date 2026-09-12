#include "Rpg/Systems/InventorySystem.h"

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/EquipmentComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Entities/Character.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Systems/StatusModifierSystem.h"

namespace Rpg {

InventorySystem::InventorySystem(EntityManager& entityManager, StatusModifierSystem& modifierSystem)
    : m_entityManager {entityManager}, m_modifierSystem {modifierSystem} {}

void InventorySystem::useConsumable(const Consumable& consumable, IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target || !target->consumables().contains(consumable.id)) return;

  m_modifierSystem.addModifier(consumable.modifier, target->id());
  target->consumables().remove(consumable.id);
}

void InventorySystem::unequipWeapon(IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target || !target->equipment().weapon.has_value()) return;

  m_modifierSystem.removeModifier(target->equipment().weapon->id, target->id());
  target->weapons().add(*target->equipment().weapon);
  target->equipment().weapon.reset();
}

void InventorySystem::unequipArmor(IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target || !target->equipment().armor.has_value()) return;

  m_modifierSystem.removeModifier(target->equipment().armor->id, target->id());
  target->armor().add(*target->equipment().armor);
  target->equipment().armor.reset();
}

void InventorySystem::equipWeapon(const Weapon& weapon, IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target || !target->weapons().contains(weapon.id)) return;

  unequipWeapon(targetId);
  m_modifierSystem.addModifier(weapon.modifier, target->id());
  target->weapons().remove(weapon.id);
  target->equipment().weapon = weapon;
}

void InventorySystem::equipArmor(const Armor& armor, IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target || !target->armor().contains(armor.id)) return;

  unequipArmor(targetId);
  m_modifierSystem.addModifier(armor.modifier, target->id());
  target->armor().remove(armor.id);
  target->equipment().armor = armor;
}

} // namespace Rpg

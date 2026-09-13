#include "Rpg/Systems/InventorySystem.h"

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/EquipmentComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Entities/Character.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Systems/ModifierSystem.h"

#include <utility>

namespace Rpg {

InventorySystem::InventorySystem(EntityManager& entityManager, ModifierSystem& modifierSystem)
    : m_entityManager {entityManager}, m_modifierSystem {modifierSystem} {}

void InventorySystem::useConsumable(IdComponent consumableId, IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target) return;

  const auto consumable {target->consumables().find(consumableId)};

  if (consumable->hasStatusModifier()) {
    m_modifierSystem.addStatusModifier(consumable->statusModifier, target->id());
  }

  if (consumable->hasInstantModifier()) {
    m_modifierSystem.applyInstantModifier(consumable->instantModifier, target->id());
  }
}

void InventorySystem::unequipWeapon(IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target) return;

  const auto previous {target->equipment().weapon};
  target->unequipWeapon();

  if (previous->hasStatusModifier()) {
    m_modifierSystem.removeStatusModifier(previous->id, target->id());
  }
}

void InventorySystem::unequipArmor(IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target) return;

  const auto previous {target->equipment().armor};
  target->unequipArmor();

  if (previous->hasStatusModifier()) {
    m_modifierSystem.removeStatusModifier(previous->id, target->id());
  }
}

void InventorySystem::equipWeapon(IdComponent weaponId, IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target) return;

  const auto weapon {std::move(*target->weapons().find(weaponId))};
  target->equipWeapon(weaponId);

  if (weapon.hasStatusModifier()) {
    m_modifierSystem.addStatusModifier(weapon.modifier, target->id());
  }
}

void InventorySystem::equipArmor(IdComponent armorId, IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target) return;

  const auto armor {std::move(*target->armor().find(armorId))};
  target->equipArmor(armorId);

  if (armor.hasStatusModifier()) {
    m_modifierSystem.addStatusModifier(armor.modifier, target->id());
  }
}

} // namespace Rpg

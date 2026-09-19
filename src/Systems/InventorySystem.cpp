#include "Folio/Systems/InventorySystem.h"

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Components/EquipmentComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Entities/Character.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Consumable.h"
#include "Folio/Items/Weapon.h"
#include "Folio/Systems/ModifierSystem.h"

namespace Folio {

InventorySystem::InventorySystem(EntityManager& entityManager, ModifierSystem& modifierSystem)
    : m_entityManager {entityManager}, m_modifierSystem {modifierSystem} {}

void InventorySystem::useConsumable(IdComponent consumableId, IdComponent sourceId,
                                    IdComponent targetId) const {
  auto source {m_entityManager.find<Character>(sourceId)};
  if (!source) return;

  auto target {m_entityManager.find<Combatant>(targetId)};
  if (!target) return;

  const auto consumable {source->consumables().find(consumableId)};
  if (consumable == source->consumables().end()) return;

  if (consumable->hasStatusModifier()) {
    m_modifierSystem.addStatusModifier(consumable->statusModifier, source->id(), target->id());
  }

  if (consumable->hasInstantModifier()) {
    m_modifierSystem.applyInstantModifier(consumable->instantModifier, source->id(), target->id());
  }

  source->useConsumable(consumableId);
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

  target->equipWeapon(weaponId);

  if (target->equipment().weapon->hasStatusModifier()) {
    m_modifierSystem.addStatusModifier(target->equipment().weapon->modifier, targetId, targetId);
  }
}

void InventorySystem::equipArmor(IdComponent armorId, IdComponent targetId) const {
  auto target {m_entityManager.find<Character>(targetId)};
  if (!target) return;

  target->equipArmor(armorId);

  if (target->equipment().armor->hasStatusModifier()) {
    m_modifierSystem.addStatusModifier(target->equipment().armor->modifier, targetId, targetId);
  }
}

} // namespace Folio

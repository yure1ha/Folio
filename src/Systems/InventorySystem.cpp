#include "Rpg/Systems/InventorySystem.h"

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/EquipmentComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Entities/Character.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Modifiers/StatusModifierType.h"

#include <cstdint>

namespace Rpg {

InventorySystem::InventorySystem(EntityManager& entityManager,
                                 ModifierEventManager& modifierEventManager)
    : m_entityManager {entityManager}, m_modifierEventManager {modifierEventManager} {}

void InventorySystem::useConsumable(const Consumable& consumable, InstanceId targetId) const {
    auto target {m_entityManager.find<Character>(targetId)};
    if (!target || !target->consumables().contains(consumable.id)) return;

    const ApplyStatusModifierEvent event {.modifier = consumable.modifier, .targetId = targetId};

    if (consumable.modifier.type != StatusModifierType::None) {
        m_modifierEventManager.dispatch(event);
    }

    target->consumables().remove(consumable.id);
}

void InventorySystem::unequipWeapon(InstanceId targetId) const {
    auto target {m_entityManager.find<Character>(targetId)};
    if (!target || !target->equipment().weapon.has_value()) return;

    target->weapons().add(*target->equipment().weapon);
    target->equipment().weapon.reset();
}

void InventorySystem::unequipArmor(InstanceId targetId) const {
    auto target {m_entityManager.find<Character>(targetId)};
    if (!target || !target->equipment().armor.has_value()) return;

    target->armor().add(*target->equipment().armor);
    target->equipment().armor.reset();
}

void InventorySystem::equipWeapon(const Weapon& weapon, InstanceId targetId) const {
    auto target {m_entityManager.find<Character>(targetId)};
    if (!target || !target->weapons().contains(weapon.id)) return;

    unequipWeapon(targetId);
    target->weapons().remove(weapon.id);
    target->equipment().weapon = weapon;

    const ApplyStatusModifierEvent event {.modifier = weapon.modifier, .targetId = targetId};

    if (weapon.modifier.type != StatusModifierType::None) {
        m_modifierEventManager.dispatch(event);
    }
}

void InventorySystem::equipArmor(const Armor& armor, InstanceId targetId) const {
    auto target {m_entityManager.find<Character>(targetId)};
    if (!target || !target->armor().contains(armor.id)) return;

    unequipArmor(targetId);
    target->armor().remove(armor.id);
    target->equipment().armor = armor;

    const ApplyStatusModifierEvent event {.modifier = armor.modifier, .targetId = targetId};

    if (armor.modifier.type != StatusModifierType::None) {
        m_modifierEventManager.dispatch(event);
    }
}

} // namespace Rpg

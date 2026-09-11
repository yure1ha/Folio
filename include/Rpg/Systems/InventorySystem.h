#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Concepts/ContainerItem.h"
#include "Rpg/Entities/EntityManager.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"

#include <cstdint>

namespace Rpg {

class InventorySystem {
  public:
    using ConsumableInventory = ContainerComponent<Consumable>;
    using WeaponInventory = ContainerComponent<Weapon>;
    using ArmorInventory = ContainerComponent<Armor>;

    InventorySystem(EntityManager& entityManager, ModifierEventManager& modifierEventManager);

    template <Concepts::ContainerItem T>
    static void addItem(const T& item, ContainerComponent<T>& inventory) {
        inventory.add(item);
    }

    template <Concepts::ContainerItem T>
    static void removeItem(const T& item, ContainerComponent<T>& inventory) {
        inventory.remove(item.id);
    }

    void useConsumable(const Consumable& consumable, InstanceId targetId) const;
    void unequipWeapon(InstanceId targetId) const;
    void unequipArmor(InstanceId targetId) const;
    void equipWeapon(const Weapon& weapon, InstanceId targetId) const;
    void equipArmor(const Armor& armor, InstanceId targetId) const;

  private:
    EntityManager& m_entityManager;
    ModifierEventManager& m_modifierEventManager;
};

} // namespace Rpg

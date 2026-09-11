#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Entities/CharacterBlueprint.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"

namespace Rpg {

class Character : public Combatant {
  public:
    using ConsumableInventory = ContainerComponent<Consumable>;
    using WeaponInventory = ContainerComponent<Weapon>;
    using ArmorInventory = ContainerComponent<Armor>;

    explicit Character(const CharacterBlueprint& bp);

    ConsumableInventory& consumables() {
        return m_consumables;
    }

    WeaponInventory& weapons() {
        return m_weapons;
    }

    ArmorInventory& armor() {
        return m_armor;
    }

    const ConsumableInventory& consumables() const {
        return m_consumables;
    }

    const WeaponInventory& weapons() const {
        return m_weapons;
    }

    const ArmorInventory& armor() const {
        return m_armor;
    }

  private:
    ConsumableInventory m_consumables;
    WeaponInventory m_weapons;
    ArmorInventory m_armor;
};

} // namespace Rpg

#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/EquipmentComponent.h"
#include "Rpg/Components/HealthComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Entities/Entity.h"
#include "Rpg/Modifiers/StatusModifier.h"

namespace Rpg {

class Combatant : public Entity {
  public:
    using ModifierList = ContainerComponent<StatusModifier>;

    Combatant(IdComponent id, HealthComponent health, StrengthComponent strength,
              DefenseComponent defense, EquipmentComponent equipment, ModifierList modifiers);

    HealthComponent& health() {
        return m_health;
    }

    StrengthComponent& strength() {
        return m_strength;
    }

    DefenseComponent& defense() {
        return m_defense;
    }

    EquipmentComponent& equipment() {
        return m_equipment;
    }

    ModifierList& modifiers() {
        return m_modifiers;
    }

    const HealthComponent& health() const {
        return m_health;
    }

    const StrengthComponent& strength() const {
        return m_strength;
    }

    const DefenseComponent& defense() const {
        return m_defense;
    }

    const EquipmentComponent& equipment() const {
        return m_equipment;
    }

    const ModifierList& modifiers() const {
        return m_modifiers;
    }

  private:
    HealthComponent m_health;
    StrengthComponent m_strength;
    DefenseComponent m_defense;
    EquipmentComponent m_equipment;
    ModifierList m_modifiers;
};

} // namespace Rpg

#include "Rpg/Entities/Combatant.h"

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/EquipmentComponent.h"
#include "Rpg/Components/HealthComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Entities/Entity.h"

#include <utility>

namespace Rpg {

Combatant::Combatant(IdComponent id, HealthComponent health, StrengthComponent strength,
                     DefenseComponent defense, EquipmentComponent equipment, ModifierList modifiers)
    : Entity {id}, m_health {std::move(health)}, m_strength {std::move(strength)},
      m_defense {std::move(defense)}, m_equipment {std::move(equipment)},
      m_modifiers {std::move(modifiers)} {}

} // namespace Rpg

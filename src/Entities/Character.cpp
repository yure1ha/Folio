#include "Rpg/Entities/Character.h"

#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/EquipmentComponent.h"
#include "Rpg/Components/HealthComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Entities/CharacterBlueprint.h"
#include "Rpg/Entities/Combatant.h"

namespace Rpg {

Character::Character(const CharacterBlueprint& bp)
    : Combatant {IdComponent {.typeId = bp.typeId},
                 HealthComponent {bp.baseHealth, bp.effectiveHealth, bp.currentHealth},
                 StrengthComponent {bp.baseStrength, bp.effectiveStrength},
                 DefenseComponent {bp.baseDefense, bp.effectiveDefense},
                 EquipmentComponent {bp.equippedWeapon, bp.equippedArmor},
                 ModifierList {bp.modifiers}},
      m_consumables {bp.consumables}, m_weapons {bp.weapons}, m_armor {bp.armor} {}

} // namespace Rpg

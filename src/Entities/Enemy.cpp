#include "Rpg/Entities/Enemy.h"

#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/HealthComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Entities/EnemyBlueprint.h"

#include <utility>

namespace Rpg {

Enemy::Enemy(EnemyBlueprint bp)
    : Combatant {IdComponent {.typeId = bp.typeId},
                 HealthComponent {bp.baseHealth, bp.effectiveHealth, bp.currentHealth},
                 StrengthComponent {bp.baseStrength, bp.effectiveStrength},
                 DefenseComponent {bp.baseDefense, bp.effectiveDefense},
                 ModifierList {std::move(bp.modifiers)}} {}

} // namespace Rpg

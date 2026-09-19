#include "Folio/Entities/Enemy.h"

#include "Folio/Components/DefenseComponent.h"
#include "Folio/Components/HealthComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StrengthComponent.h"
#include "Folio/Components/ValueComponent.h"
#include "Folio/Entities/Combatant.h"
#include "Folio/Entities/EnemyBlueprint.h"

#include <utility>

namespace Folio {

Enemy::Enemy(EnemyBlueprint bp)
    : Combatant {IdComponent {.typeId = bp.typeId},
                 HealthComponent {bp.baseHealth, bp.effectiveHealth, bp.currentHealth},
                 StrengthComponent {bp.baseStrength, bp.effectiveStrength},
                 DefenseComponent {bp.baseDefense, bp.effectiveDefense},
                 ModifierList {std::move(bp.modifiers)}},
      m_exp {.base = bp.baseExp} {}

} // namespace Folio

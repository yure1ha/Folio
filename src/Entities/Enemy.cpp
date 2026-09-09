#include "Rpg/Entities/Enemy.h"

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Entities/EnemyBlueprint.h"

namespace Rpg
{

Enemy::Enemy(IdComponent id, const EnemyBlueprint& bp)
    : Entity(id),
      m_health    {bp.baseHealth, bp.effectiveHealth, bp.currentHealth},
      m_strength  {bp.baseStrength, bp.effectiveStrength},
      m_defense   {bp.baseDefense, bp.effectiveDefense},
      m_equipment {bp.equippedWeapon, bp.equippedArmor},
      m_modifiers {bp.modifiers}
{
}

} // namespace Rpg

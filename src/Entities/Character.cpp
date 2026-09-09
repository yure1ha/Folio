#include "Rpg/Entities/Character.h"

#include "Rpg/Entities/Entity.h"
#include "Rpg/Entities/CharacterBlueprint.h"

#include "Rpg/Components/IdComponent.h"

namespace Rpg
{

Character::Character(IdComponent id, const CharacterBlueprint& bp)
    : Entity(id),
      m_health      {bp.baseHealth, bp.effectiveHealth, bp.currentHealth},
      m_strength    {bp.baseStrength, bp.effectiveStrength},
      m_defense     {bp.baseDefense, bp.effectiveDefense},
      m_equipment   {bp.equippedWeapon, bp.equippedArmor},
      m_consumables {bp.consumables},
      m_weapons     {bp.weapons},
      m_armor       {bp.armor},
      m_modifiers   {bp.modifiers}
{
}

} // namespace Rpg

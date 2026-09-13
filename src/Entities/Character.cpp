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
                 ModifierList {bp.modifiers}},
      m_equipment {.weapon = bp.equippedWeapon, .armor = bp.equippedArmor},
      m_consumables {std::move(bp.consumables)}, m_weapons {std::move(bp.weapons)},
      m_armor {std::move(bp.armor)} {}

void Character::useConsumable(IdComponent consumableId) {
  if (!m_consumables.contains(consumableId)) return;
  m_consumables.remove(consumableId);
}

void Character::unequipWeapon() {
  if (!m_equipment.weapon.has_value()) return;

  m_weapons.add(std::move(*m_equipment.weapon));
  m_equipment.weapon.reset();
}

void Character::unequipArmor() {
  if (!m_equipment.armor.has_value()) return;

  m_armor.add(std::move(*m_equipment.armor));
  m_equipment.armor.reset();
}

void Character::equipWeapon(IdComponent weaponId) {
  const auto it {m_weapons.find(weaponId)};
  if (it == m_weapons.end()) return;

  auto weapon {*it};
  m_weapons.remove(weaponId);

  unequipWeapon();
  m_equipment.weapon = std::move(weapon);
}

void Character::equipArmor(IdComponent armorId) {
  const auto it {m_armor.find(armorId)};
  if (it == m_armor.end()) return;

  auto armor {*it};
  m_armor.remove(armorId);

  unequipArmor();
  m_equipment.armor = std::move(armor);
}

} // namespace Rpg

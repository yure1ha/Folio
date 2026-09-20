#include "Folio/Entities/Character.h"

#include "Folio/Components/DefenseComponent.h"
#include "Folio/Components/EquipmentComponent.h"
#include "Folio/Components/HealthComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StrengthComponent.h"
#include "Folio/Components/ValueComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Entities/CharacterBlueprint.h"
#include "Folio/Entities/Combatant.h"

#include <utility>

namespace Folio {

Character::Character(const CharacterBlueprint& bp)
    : Combatant {IdComponent {.typeId = bp.typeId},
                 ValueComponent {.base = bp.currentExp},
                 HealthComponent {bp.baseHealth, bp.effectiveHealth, bp.currentHealth},
                 StrengthComponent {bp.baseStrength, bp.effectiveStrength},
                 DefenseComponent {bp.baseDefense, bp.effectiveDefense},
                 ModifierList {bp.modifiers}},
      m_equipment {.weapon = bp.equippedWeapon, .armor = bp.equippedArmor},
      m_consumables {std::move(bp.consumables)}, m_weapons {std::move(bp.weapons)},
      m_armor {std::move(bp.armor)} {}

void Character::levelUp() {
  m_level++;
}

void Character::gainExp(Experience delta) {
  increaseExp(delta);

  while (levelable() && exp().base >= totalRequiredExp()) {
    decreaseExp(totalRequiredExp());
    levelUp();
  }
}

Experience Character::totalRequiredExp() const {
  return (kQuadraticMultiplier * m_level * m_level) + (kLinearMultiplier * m_level) + kBaseValue;
}

Experience Character::requiredExp() const {
  return totalRequiredExp() - exp().base;
}

void Character::addItem(Consumable consumable) {
  m_consumables.add(std::move(consumable));
}

void Character::addItem(Weapon weapon) {
  m_weapons.add(std::move(weapon));
}

void Character::addItem(Armor armor) {
  m_armor.add(std::move(armor));
}

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
  auto it {m_weapons.find(weaponId)};
  if (it == m_weapons.end()) return;

  m_weapons.remove(it);
  unequipWeapon();
  m_equipment.weapon = std::move(*it);
}

void Character::equipArmor(IdComponent armorId) {
  auto it {m_armor.find(armorId)};
  if (it == m_armor.end()) return;

  m_armor.remove(it);
  unequipArmor();
  m_equipment.armor = std::move(*it);
}

} // namespace Folio

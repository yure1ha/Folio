#pragma once

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Components/Containers.h"
#include "Folio/Components/EquipmentComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Entities/CharacterBlueprint.h"
#include "Folio/Entities/Combatant.h"
#include "Folio/Entities/EntityType.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Consumable.h"
#include "Folio/Items/Weapon.h"

#include <cstdint>

namespace Folio {

class Character : public Combatant {
public:
  explicit Character(const CharacterBlueprint& bp);

  EntityType type() const override { return EntityType::Character; }

  Level level() const { return m_level; }
  bool levelable() const { return m_level < kMaxLevel; }

  const EquipmentComponent& equipment() const { return m_equipment; }
  const ConsumableInventory& consumables() const { return m_consumables; }

  void levelUp();
  void gainExp(Experience delta);
  Experience totalRequiredExp() const;
  Experience requiredExp() const;

  void addItem(Consumable consumable);
  void useConsumable(IdComponent consumableId);

  void addWeapon(Weapon weapon) { m_equipment.addWeapon(weapon); }
  void addArmor(Armor armor) { m_equipment.addArmor(armor); }

  bool unequipWeapon() {
    if (!m_equipment.unequipWeapon()) return false;
    return true;
  }

  bool unequipArmor() {
    if (!m_equipment.unequipArmor()) return false;
    return true;
  }

  bool equipWeapon(IdComponent weaponId) {
    if (!m_equipment.equipWeapon(weaponId)) return false;
    return true;
  }

  bool equipArmor(IdComponent armorId) {
    if (!m_equipment.equipArmor(armorId)) return false;
    return true;
  }

private:
  static constexpr Level kMinLevel {1};
  static constexpr Level kMaxLevel {50};

  static constexpr std::int32_t kQuadraticMultiplier {15};
  static constexpr std::int32_t kLinearMultiplier {100};
  static constexpr std::int32_t kBaseValue {100};

  Level m_level {};

  EquipmentComponent m_equipment;
  ConsumableInventory m_consumables;
};

} // namespace Folio

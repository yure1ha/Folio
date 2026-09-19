#pragma once

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Components/EquipmentComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Entities/CharacterBlueprint.h"
#include "Folio/Entities/Combatant.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Consumable.h"
#include "Folio/Items/Weapon.h"

#include <cstdint>

namespace Folio {

class Character : public Combatant {
public:
  using ConsumableInventory = ContainerComponent<Consumable>;
  using WeaponInventory = ContainerComponent<Weapon>;
  using ArmorInventory = ContainerComponent<Armor>;

  explicit Character(const CharacterBlueprint& bp);

  Level level() const { return m_level; }
  Experience currentExp() const { return m_currentExp; }
  bool levelable() const { return m_level < kMaxLevel; }

  const EquipmentComponent& equipment() const { return m_equipment; }
  const ConsumableInventory& consumables() const { return m_consumables; }
  const WeaponInventory& weapons() const { return m_weapons; }
  const ArmorInventory& armor() const { return m_armor; }

  void levelUp();
  void gainExp(Experience exp);
  Experience totalRequiredExp() const;
  Experience requiredExp() const;

  void addItem(Consumable consumable);
  void addItem(Weapon weapon);
  void addItem(Armor armor);

  void useConsumable(IdComponent consumableId);
  void unequipWeapon();
  void unequipArmor();
  void equipWeapon(IdComponent weaponId);
  void equipArmor(IdComponent armorId);

private:
  static constexpr Level kMinLevel {1};
  static constexpr Level kMaxLevel {50};

  static constexpr std::int32_t kQuadraticMultiplier {15};
  static constexpr std::int32_t kLinearMultiplier {100};
  static constexpr std::int32_t kBaseValue {100};

  Level m_level {};
  Experience m_currentExp {};

  EquipmentComponent m_equipment;
  ConsumableInventory m_consumables;
  WeaponInventory m_weapons;
  ArmorInventory m_armor;
};

} // namespace Folio

#pragma once

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Components/Containers.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Weapon.h"

#include <optional>
#include <utility>

namespace Folio {

class EquipmentComponent {
public:
  using EquippedWeapon = std::optional<Weapon>;
  using EquippedArmor = std::optional<Armor>;

  EquipmentComponent() = default;

  EquipmentComponent(Weapon weapon, Armor armor, WeaponInventory weapons, ArmorInventory armors)
      : m_weapon {std::move(weapon)}, m_armor {std::move(armor)}, m_weapons {std::move(weapons)},
        m_armors {std::move(armors)} {}

  const EquippedWeapon& weapon() const { return m_weapon; }
  const EquippedArmor& armor() const { return m_armor; }

  const WeaponInventory& weapons() const { return m_weapons; }
  const ArmorInventory& armors() const { return m_armors; }

  void addWeapon(Weapon weapon) { m_weapons.add(std::move(weapon)); }
  void addArmor(Armor armor) { m_armors.add(std::move(armor)); }

  bool unequipWeapon() {
    if (!m_weapon.has_value()) return false;

    m_weapons.add(std::move(*m_weapon));
    m_weapon.reset();

    return true;
  }

  bool unequipArmor() {
    if (!m_armor.has_value()) return false;

    m_armors.add(std::move(*m_armor));
    m_armor.reset();

    return true;
  }

  bool equipWeapon(IdComponent weaponId) {
    auto it {m_weapons.find(weaponId)};
    if (it == m_weapons.end()) return false;

    auto weapon {std::move(*it)};
    m_weapons.remove(it);

    unequipWeapon();
    m_weapon = std::move(weapon);

    return true;
  }

  bool equipArmor(IdComponent armorId) {
    auto it {m_armors.find(armorId)};
    if (it == m_armors.end()) return false;

    auto armor {std::move(*it)};
    m_armors.remove(it);

    unequipArmor();
    m_armor = std::move(armor);

    return true;
  }

private:
  EquippedWeapon m_weapon;
  EquippedArmor m_armor;
  WeaponInventory m_weapons;
  ArmorInventory m_armors;
};

} // namespace Folio

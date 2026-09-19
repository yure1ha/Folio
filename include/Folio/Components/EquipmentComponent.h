#pragma once

#include "Folio/Items/Armor.h"
#include "Folio/Items/Weapon.h"

#include <optional>

namespace Folio {

struct EquipmentComponent {
  std::optional<Weapon> weapon;
  std::optional<Armor> armor;
};

} // namespace Folio

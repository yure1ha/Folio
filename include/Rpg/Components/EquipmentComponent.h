#pragma once

#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Weapon.h"

#include <optional>

namespace Rpg {

struct EquipmentComponent {
    std::optional<Weapon> weapon;
    std::optional<Armor> armor;
};

} // namespace Rpg

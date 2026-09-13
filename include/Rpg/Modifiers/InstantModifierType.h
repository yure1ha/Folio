#pragma once

#include <cstdint>

namespace Rpg {

enum class InstantModifierType : std::uint8_t {
  None,
  Heal,
  Damage,
};

} // namespace Rpg

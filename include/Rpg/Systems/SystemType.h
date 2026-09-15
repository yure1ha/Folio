#pragma once

#include <cstdint>

namespace Rpg {

enum class SystemType : std::uint8_t {
  None,
  StatusModifier,
  Combat,
  Inventory,
  Turn,
};

} // namespace Rpg

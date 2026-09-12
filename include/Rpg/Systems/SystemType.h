#pragma once

#include <cstdint>

namespace Rpg {

enum class SystemType : std::uint8_t {
  StatusModifier,
  Combat,
  Inventory,
};

} // namespace Rpg

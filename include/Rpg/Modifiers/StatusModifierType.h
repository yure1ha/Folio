#pragma once

#include <cstdint>

namespace Rpg
{

enum class StatusModifierType : std::uint8_t
{
  Health,
  Strength,
  Defense,
  None,
};

} // namespace Rpg

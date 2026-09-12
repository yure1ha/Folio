#pragma once

#include "Rpg/Core/Types.h"

#include <compare>

namespace Rpg {

struct IdComponent {
  TypeId typeId {};
  InstanceId instanceId {};

  auto operator<=>(const IdComponent&) const = default;
};

} // namespace Rpg

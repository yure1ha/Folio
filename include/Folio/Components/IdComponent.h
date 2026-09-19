#pragma once

#include "Folio/Core/Types.h"

#include <compare>

namespace Folio {

struct IdComponent {
  TypeId typeId {};
  InstanceId instanceId {};

  auto operator<=>(const IdComponent&) const = default;
};

} // namespace Folio

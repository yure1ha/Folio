#pragma once

#include <compare>
#include <cstdint>

namespace Rpg {

using InstanceId = std::int32_t;
using TypeId = std::int32_t;

struct IdComponent {
    TypeId typeId {};
    InstanceId instanceId {};

    auto operator<=>(const IdComponent&) const = default;
};

} // namespace Rpg

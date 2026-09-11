#pragma once

#include "Rpg/Modifiers/StatusModifierType.h"

#include <concepts>
#include <cstdint>

namespace Rpg::Concepts {

template <typename T>
concept AttributeComponent = requires(T& attr, std::int32_t amount) {
    { T::kModifierType } -> std::same_as<const StatusModifierType&>;
    { attr.base() } -> std::same_as<std::int32_t>;
    { attr.effective() } -> std::same_as<std::int32_t>;
    { attr.increase(amount) };
    { attr.decrease(amount) };
    { attr.reset() };
};

} // namespace Rpg::Concepts

#pragma once

#include "Rpg/Modifiers/StatusModifierType.h"

#include <concepts>
#include <cstdint>

namespace Rpg::Concepts {

template <typename T>
concept AttributeComponent = requires(T& attr, std::int32_t amount) {
  { T::type() } -> std::same_as<StatusModifierType>;
  { attr.base() } -> std::same_as<std::int32_t>;
  { attr.effective() } -> std::same_as<std::int32_t>;
  { attr.increase(amount) };
  { attr.decrease(amount) };
  { attr.reset() };
};

} // namespace Rpg::Concepts

#pragma once

#include <cmath>
#include <cstdint>

namespace Folio {

struct ValueComponent {
  static constexpr std::int32_t kMinMultiplier {1};

  std::int32_t base {};
  std::int32_t multiplier {};

  std::int32_t total() const {
    if (multiplier < kMinMultiplier) return base;

    const auto result {static_cast<double>(base) * (1.0 + multiplier / 100.0)};

    return static_cast<std::int32_t>(std::lround(result));
  }
};

} // namespace Folio

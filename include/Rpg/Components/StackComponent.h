#pragma once

#include "Rpg/Core/Types.h"

#include <algorithm>

namespace Rpg {

class StackComponent {
public:
  StackComponent() = default;

  StackComponent(Stack max, Stack current) : m_max {max}, m_current {current} {
    clamp();
  }

  Stack max() const {
    return m_max;
  }

  Stack current() const {
    return m_current;
  }

  bool empty() const {
    return m_current < kMinAmount;
  }

  void increase(Stack delta) {
    if (delta <= 0) return;

    m_current += delta;
    clamp();
  }

  void decrease(Stack delta) {
    if (delta <= 0) return;

    m_current -= delta;
    clamp();
  }

private:
  static constexpr Stack kMinAmount {1};

  void clamp() {
    m_current = std::clamp(m_current, kMinAmount, m_max);
    m_max = std::clamp(m_max, kMinAmount, m_max);
  }

  Stack m_max {kMinAmount};
  Stack m_current {kMinAmount};
};

} // namespace Rpg

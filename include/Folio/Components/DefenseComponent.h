#pragma once

#include "Folio/Core/Types.h"
#include "Folio/Modifiers/StatusModifierType.h"

#include <algorithm>

namespace Folio {

class DefenseComponent {
public:
  explicit DefenseComponent(Defense base) : DefenseComponent {base, base} {}

  DefenseComponent(Defense base, Defense effective) : m_base {base}, m_effective {effective} {
    clamp();
  };

  static constexpr StatusModifierType type() { return StatusModifierType::Defense; }
  Defense base() const { return m_base; }
  Defense effective() const { return m_effective; }

  void increase(Defense delta) {
    if (delta <= 0) return;

    m_effective += delta;
    clamp();
  }

  void decrease(Defense amount) {
    if (amount <= 0) return;

    m_effective -= amount;
    clamp();
  }

  void reset() {
    m_effective = m_base;
    clamp();
  }

private:
  static constexpr Defense kMinDefense {1};
  static constexpr Defense kMaxDefense {99};

  void clamp() {
    m_base = std::clamp(m_base, kMinDefense, kMaxDefense);
    m_effective = std::clamp(m_effective, kMinDefense, kMaxDefense);
  }

  Defense m_base {};
  Defense m_effective {};
};

} // namespace Folio

#pragma once

#include "Folio/Core/Types.h"
#include "Folio/Modifiers/StatusModifierType.h"

#include <algorithm>

namespace Folio {

class StrengthComponent {
public:
  explicit StrengthComponent(Strength base) : StrengthComponent {base, base} {}

  StrengthComponent(Strength base, Strength effective) : m_base {base}, m_effective {effective} {
    clamp();
  }

  static constexpr StatusModifierType type() { return StatusModifierType::Strength; }
  Strength base() const { return m_base; }
  Strength effective() const { return m_effective; }

  void increase(Strength delta) {
    if (delta <= 0) return;

    m_effective += delta;
    clamp();
  }

  void decrease(Strength delta) {
    if (delta <= 0) return;

    m_effective -= delta;
    clamp();
  }

  void reset() {
    m_effective = m_base;
    clamp();
  }

private:
  static constexpr Strength kMinStrength {1};
  static constexpr Strength kMaxStrength {99};

  void clamp() {
    m_base = std::clamp(m_base, kMinStrength, kMaxStrength);
    m_effective = std::clamp(m_effective, kMinStrength, kMaxStrength);
  }

  Strength m_base {};
  Strength m_effective {};
};

} // namespace Folio

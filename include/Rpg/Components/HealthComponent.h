#pragma once

#include "Rpg/Core/Types.h"
#include "Rpg/Modifiers/StatusModifierType.h"

#include <algorithm>
#include <cstdint>

namespace Rpg {

class HealthComponent {
public:
  explicit HealthComponent(Health base) : HealthComponent {base, base, base} {}

  HealthComponent(Health base, Health effective, Health current)
      : m_base {base}, m_effective {effective}, m_current {current} {
    clamp();
  }

  static constexpr StatusModifierType type() {
    return StatusModifierType::Health;
  }

  Health base() const {
    return m_base;
  }

  Health effective() const {
    return m_effective;
  }

  Health current() const {
    return m_current;
  }

  bool alive() const {
    return m_current > kMinHealth;
  }

  void increase(std::int32_t amount) {
    if (amount <= 0) return;

    m_effective += amount;
    clamp();
  }

  void decrease(std::int32_t amount) {
    if (amount <= 0) return;

    m_effective -= amount;
    clamp();
  }

  void heal(std::int32_t amount) {
    if (amount <= 0) return;

    m_current += amount;
    clamp();
  }

  void takeDamage(std::int32_t amount) {
    if (amount <= 0) return;

    m_current -= amount;
    clamp();
  }

  void healFull() {
    m_current = m_effective;
  }

  void reset() {
    m_effective = m_base;
    clamp();
  }

private:
  static constexpr Health kMinHealth {0};
  static constexpr Health kMaxHealth {9999};

  void clamp() {
    m_base = std::clamp(m_base, kMinHealth, kMaxHealth);
    m_effective = std::clamp(m_effective, kMinHealth, kMaxHealth);
    m_current = std::clamp(m_current, kMinHealth, m_effective);
  }

  Health m_base {};
  Health m_effective {};
  Health m_current {};
};

} // namespace Rpg

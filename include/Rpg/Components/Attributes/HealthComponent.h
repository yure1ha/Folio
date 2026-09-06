#pragma once

#include "Rpg/Data/StatusModifierType.h"

#include <algorithm>
#include <cstdint>

namespace Rpg
{

class HealthComponent
{
public:
  HealthComponent(std::int32_t base, std::int32_t effective, std::int32_t current)
      : m_effective {effective},
        m_base      {base},
        m_current   {current}
  {
    clamp();
  }

  static constexpr std::int32_t kMinHealth {0};
  static constexpr std::int32_t kMaxHealth {9999};
  static constexpr auto         kModifierType {StatusModifierType::Health};

  std::int32_t base() const      { return m_base; }
  std::int32_t effective() const { return m_effective; }
  std::int32_t current() const   { return m_current; }
  bool alive() const             { return m_current > kMinHealth; }

  void increase(std::int32_t amount)
  {
    if (amount <= 0) return;

    m_effective += amount;
    clamp();
  }

  void decrease(std::int32_t amount)
  {
    if (amount <= 0) return;

    m_effective -= amount;
    clamp();
  }

  void heal(std::int32_t amount)
  {
    if (amount <= 0) return;

    m_current += amount;
    clamp();
  }

  void takeDamage(std::int32_t amount)
  {
    if (amount <= 0) return;

    m_current -= amount;
    clamp();
  }

  void healFull()
  {
    m_current = m_effective;
  }

  void reset()
  {
    m_effective = m_base;
    clamp();
  }

private:
  void clamp()
  {
    m_base      = std::clamp(m_base, kMinHealth, kMaxHealth);
    m_effective = std::clamp(m_effective, kMinHealth, kMaxHealth);
    m_current   = std::clamp(m_current, kMinHealth, m_effective);
  }

  std::int32_t m_base {};
  std::int32_t m_effective {};
  std::int32_t m_current {};
};

} // namespace Rpg

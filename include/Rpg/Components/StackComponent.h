#pragma once

#include <algorithm>
#include <cstdint>

namespace Rpg {

class StackComponent {
  public:
    StackComponent(std::int32_t max, std::int32_t current) : m_max {max}, m_current {current} {
        clamp();
    }

    static constexpr std::int32_t kMinAmount {1};

    std::int32_t max() const {
        return m_max;
    }

    std::int32_t current() const {
        return m_current;
    }

    bool empty() const {
        return m_current < kMinAmount;
    }

    void increase(std::int32_t amount) {
        if (amount <= 0) return;

        m_current += amount;
        clamp();
    }

    void decrease(std::int32_t amount) {
        if (amount <= 0) return;

        m_current -= amount;
        clamp();
    }

  private:
    void clamp() {
        m_current = std::clamp(m_current, kMinAmount, m_max);
        m_max = std::clamp(m_max, kMinAmount, m_max);
    }

    std::int32_t m_max {};
    std::int32_t m_current {};
};

} // namespace Rpg

#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace Rpg {

class IdFactory {
  public:
    IdFactory() = default;

    static constexpr std::int32_t kMinInstanceId {1};

    InstanceId allocate() {
        if (!m_freeIds.empty()) {
            const std::int32_t instanceId {m_freeIds.back()};
            m_freeIds.pop_back();

            return instanceId;
        }

        return m_instanceId++;
    }

    void free(InstanceId id) {
        if (id < kMinInstanceId || id >= m_instanceId) return;
        if (std::ranges::find(m_freeIds, id) != m_freeIds.end()) return;

        m_freeIds.push_back(id);
    }

  private:
    std::vector<std::int32_t> m_freeIds {};
    std::int32_t m_instanceId {kMinInstanceId};
};

} // namespace Rpg

#pragma once

#include "Rpg/Core/Types.h"

#include <algorithm>
#include <vector>

namespace Rpg {

class IdFactory {
public:
  InstanceId allocate() {
    if (!m_freeIds.empty()) {
      const auto instanceId {m_freeIds.back()};
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
  static constexpr InstanceId kMinInstanceId {1};

  std::vector<InstanceId> m_freeIds {};
  InstanceId m_instanceId {kMinInstanceId};
};

} // namespace Rpg

#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Entities/Entity.h"
#include "Rpg/Factories/IdFactory.h"

#include <memory>
#include <unordered_map>
#include <utility>

namespace Rpg {

class EntityManager {
public:
  template <typename T>
  const T* find(IdComponent id) const {
    if (const auto it {m_entities.find(id.instanceId)}; it != m_entities.end()) {
      return dynamic_cast<const T*>(it->second.get());
    }

    return nullptr;
  }

  template <typename T>
  T* find(IdComponent id) {
    return const_cast<T*>(std::as_const(*this).find<T>(id));
  }

  void add(EntityUPtr entity) {
    if (!entity) return;

    const auto instanceId {entity->id().instanceId};
    m_entities.try_emplace(instanceId, std::move(entity));
  }

  void destroy(IdComponent id) {
    m_entities.erase(id.instanceId);
  }

private:
  std::unordered_map<InstanceId, EntityUPtr> m_entities {};
};

} // namespace Rpg

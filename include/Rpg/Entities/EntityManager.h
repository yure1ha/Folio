#pragma once

#include "Rpg/Entities/Entity.h"
#include "Rpg/Factories/IdFactory.h"

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>

namespace Rpg {

class EntityManager {
  public:
    using EntityUPtr = std::unique_ptr<Entity>;

    explicit EntityManager(IdFactory& idFactory) : m_idFactory {idFactory} {}

    template <typename T>
    T* find(InstanceId id) {
        if (const auto it {m_entities.find(id)}; it != m_entities.end()) {
            return dynamic_cast<T*>(it->second.get());
        }

        return nullptr;
    }

    template <typename T>
    const T* find(InstanceId id) const {
        if (const auto it {m_entities.find(id)}; it != m_entities.end()) {
            return dynamic_cast<const T*>(it->second.get());
        }

        return nullptr;
    }

    void add(EntityUPtr entity) {
        if (!entity) return;

        const auto instanceId {m_idFactory.allocate()};
        entity->id().instanceId = instanceId;
        m_entities.try_emplace(instanceId, std::move(entity));
    }

    void destroy(InstanceId id) { m_entities.erase(id); }

  private:
    IdFactory& m_idFactory;
    std::unordered_map<std::int32_t, EntityUPtr> m_entities {};
};

} // namespace Rpg

#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Entities/Entity.h"
#include "Folio/Events/ECharacterDefeated.h"
#include "Folio/Events/EEnemyDefeated.h"
#include "Folio/Events/EHealthChanged.h"
#include "Folio/Factories/IdFactory.h"
#include "Folio/Systems/SystemType.h"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Folio {

class EntityManager {
public:
  EntityManager(IdFactory& idFactory, EHealthChangedManager& healthChangedManager,
                ECharacterDefeatedManager& characterDefeatedManager,
                EEnemyDefeatedManager& enemyDefeatedManager);

  ~EntityManager();

  EntityManager(const EntityManager&) = delete;
  EntityManager& operator=(const EntityManager&) = delete;

  EntityManager(EntityManager&&) noexcept = delete;
  EntityManager& operator=(EntityManager&&) noexcept = delete;

  static constexpr SystemType type() { return SystemType::Entity; }

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

  void add(EntityUPtr entity);
  void destroy(IdComponent id);
  void clearDestructionQueue();

private:
  void onHealthChanged(const EHealthChanged& event);
  void onCharacterDefeated(const ECharacterDefeated& event);
  void onEnemyDefeated(const EEnemyDefeated& event);

  IdFactory& m_idFactory;
  EHealthChangedManager& m_healthChangedManager;
  ECharacterDefeatedManager& m_characterDefeatedManager;
  EEnemyDefeatedManager& m_enemyDefeatedManager;

  std::unordered_map<InstanceId, EntityUPtr> m_entities {};
  std::vector<IdComponent> m_destructionQueue {};
};

} // namespace Folio

#include "Folio/Systems/EntityManager.h"

#include "Folio/Components/IdComponent.h"
#include "Folio/Entities/Character.h"
#include "Folio/Entities/Combatant.h"
#include "Folio/Entities/Entity.h"
#include "Folio/Entities/EntityType.h"
#include "Folio/Events/ECharacterDefeated.h"
#include "Folio/Events/EEnemyDefeated.h"
#include "Folio/Events/EHealthChanged.h"

#include <algorithm>
#include <utility>

namespace Folio {

EntityManager::EntityManager(IdFactory& idFactory, EHealthChangedManager& healthChangedManager,
                             ECharacterDefeatedManager& characterDefeatedManager,
                             EEnemyDefeatedManager& enemyDefeatedManager)
    : m_idFactory {idFactory}, m_healthChangedManager {healthChangedManager},
      m_characterDefeatedManager {characterDefeatedManager},
      m_enemyDefeatedManager {enemyDefeatedManager} {
  m_healthChangedManager.subscribe(type(), [this](const EHealthChanged& event) {
    onHealthChanged(event);
  });

  m_characterDefeatedManager.subscribe(type(), [this](const ECharacterDefeated& event) {
    onCharacterDefeated(event);
  });

  m_enemyDefeatedManager.subscribe(type(), [this](const EEnemyDefeated& event) {
    onEnemyDefeated(event);
  });
}

EntityManager::~EntityManager() {
  m_healthChangedManager.unsubscribe(type());
  m_characterDefeatedManager.unsubscribe(type());
  m_enemyDefeatedManager.unsubscribe(type());
}

void EntityManager::add(EntityUPtr entity) {
  if (!entity) return;

  const auto instanceId {entity->id().instanceId};
  m_entities.try_emplace(instanceId, std::move(entity));
}

void EntityManager::destroy(IdComponent id) {
  m_entities.erase(id.instanceId);
  m_idFactory.free(id.instanceId);
}

void EntityManager::clearDestructionQueue() {
  for (const auto& id : m_destructionQueue) {
    destroy(id);
  }

  m_destructionQueue.clear();
}

void EntityManager::onHealthChanged(const EHealthChanged& event) {
  const auto target {find<Combatant>(event.targetId)};
  if (!target || target->health().alive()) return;

  switch (target->type()) {
  case EntityType::None:
    break;

  case EntityType::Character:
    m_characterDefeatedManager.dispatch(
        ECharacterDefeated {.sourceId = event.sourceId, .targetId = event.targetId});
    break;

  case EntityType::Enemy:
    m_enemyDefeatedManager.dispatch(EEnemyDefeated {
        .sourceId = event.sourceId, .targetId = event.targetId, .exp = target->exp().total()});
    break;
  }
}

void EntityManager::onCharacterDefeated(const ECharacterDefeated& event) {}

void EntityManager::onEnemyDefeated(const EEnemyDefeated& event) {
  if (auto source {find<Character>(event.sourceId)}) {
    source->gainExp(event.exp);
  }

  if (std::ranges::find(m_destructionQueue, event.targetId) == m_destructionQueue.end()) {
    m_destructionQueue.push_back(event.targetId);
  }
}

} // namespace Folio

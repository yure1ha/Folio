#include "Folio/Systems/EntityManager.h"

#include "Folio/Components/IdComponent.h"
#include "Folio/Entities/Character.h"
#include "Folio/Entities/Combatant.h"
#include "Folio/Entities/Enemy.h"
#include "Folio/Entities/Entity.h"
#include "Folio/Events/ECharacterDefeated.h"
#include "Folio/Events/EEnemyDefeated.h"
#include "Folio/Events/EHealthChanged.h"

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

void EntityManager::onHealthChanged(const EHealthChanged& event) {
  auto target {find<Combatant>(event.targetId)};
  if (!target || target->health().alive()) return;

  if (const auto enemy {dynamic_cast<Enemy*>(target)}) {
    m_enemyDefeatedManager.dispatch(EEnemyDefeated {
        .sourceId = event.sourceId, .targetId = event.targetId, .exp = enemy->exp().total()});
  } else {
    m_characterDefeatedManager.dispatch(
        ECharacterDefeated {.sourceId = event.sourceId, .targetId = event.targetId});
  }
}

void EntityManager::onCharacterDefeated(const ECharacterDefeated& event) {
  // TODO: handle character defeat
}

void EntityManager::onEnemyDefeated(const EEnemyDefeated& event) {
  if (auto source {find<Character>(event.sourceId)}) {
    source->gainExp(event.exp);
  }

  destroy(event.targetId);
}

} // namespace Folio

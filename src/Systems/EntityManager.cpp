#include "Rpg/Systems/EntityManager.h"

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Entities/Entity.h"

#include <utility>

namespace Rpg {

EntityManager::EntityManager(IdFactory& idFactory) : m_idFactory {idFactory} {}

void EntityManager::add(EntityUPtr entity) {
  if (!entity) return;

  const auto instanceId {entity->id().instanceId};
  m_entities.try_emplace(instanceId, std::move(entity));
}

void EntityManager::destroy(IdComponent id) {
  m_idFactory.free(id.instanceId);
  m_entities.erase(id.instanceId);
}

} // namespace Rpg

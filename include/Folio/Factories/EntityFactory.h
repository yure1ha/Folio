#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Entities/CharacterBlueprint.h"
#include "Folio/Entities/EnemyBlueprint.h"
#include "Folio/Factories/IdFactory.h"
#include "Folio/Systems/EntityManager.h"

#include <memory>

namespace Folio {

class EntityFactory {
public:
  EntityFactory(IdFactory& idFactory, EntityManager& entityManager)
      : m_idFactory {idFactory}, m_entityManager {entityManager} {}

  template <typename Entity, typename Blueprint>
  IdComponent create(const Blueprint& bp) const {
    auto entity {std::make_unique<Entity>(bp)};
    const auto instanceId {m_idFactory.allocate()};

    entity->setInstanceId(instanceId);
    m_entityManager.add(std::move(entity));

    return IdComponent {.typeId = bp.typeId, .instanceId = instanceId};
  }

  IdComponent create(const CharacterBlueprint& bp) const { return create<Character>(bp); }
  IdComponent create(const EnemyBlueprint& bp) const { return create<Enemy>(bp); }

private:
  IdFactory& m_idFactory;
  EntityManager& m_entityManager;
};

} // namespace Folio

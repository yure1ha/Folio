#pragma once

#include "Folio/Entities/Combatant.h"
#include "Folio/Entities/EnemyBlueprint.h"
#include "Folio/Entities/EntityType.h"

namespace Folio {

class Enemy : public Combatant {
public:
  explicit Enemy(EnemyBlueprint bp);

  EntityType type() const override { return EntityType::Enemy; }
};

} // namespace Folio

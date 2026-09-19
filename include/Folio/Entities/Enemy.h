#pragma once

#include "Folio/Components/ValueComponent.h"
#include "Folio/Entities/Combatant.h"
#include "Folio/Entities/EnemyBlueprint.h"

namespace Folio {

class Enemy : public Combatant {
public:
  explicit Enemy(EnemyBlueprint bp);

  ValueComponent exp() const { return m_exp; }

private:
  ValueComponent m_exp;
};

} // namespace Folio

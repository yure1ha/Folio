#pragma once

#include "Rpg/Entities/Combatant.h"
#include "Rpg/Entities/EnemyBlueprint.h"

namespace Rpg {

class Enemy : public Combatant {
public:
  explicit Enemy(EnemyBlueprint bp);
};

} // namespace Rpg

#pragma once

#include "Rpg/Entities/Combatant.h"

#include <iostream>

namespace Rpg::Tests {

inline void printCombatant(const Combatant& combatant) {
  std::cout << "[ID] " << combatant.id().instanceId << "/" << combatant.id().typeId << " "
            << "[HP] " << combatant.health().current() << "/" << combatant.health().effective()
            << "/" << combatant.health().base() << " "
            << "[STR] " << combatant.strength().effective() << "/" << combatant.strength().base()
            << " "
            << "[DEF] " << combatant.defense().effective() << "/" << combatant.defense().base()
            << '\n';
}

} // namespace Rpg::Tests

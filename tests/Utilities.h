#pragma once

#include "Rpg/Entities/Combatant.h"

#include <string>

namespace Rpg::Tests {

std::string formatAttribute(int base, int effective, int width);
std::string healthBar(int effective, int current, int width);
void printCombatant(const Combatant& combatant);

} // namespace Rpg::Tests

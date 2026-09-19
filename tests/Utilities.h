#pragma once

#include "Folio/Entities/Combatant.h"

#include <string>

namespace Folio::Tests {

std::string formatAttribute(int base, int effective, int width);
std::string healthBar(int effective, int current, int width);
void printCombatant(const Combatant& combatant);

} // namespace Folio::Tests

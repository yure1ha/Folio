#include "Utilities.h"

#include "Rpg/Entities/Combatant.h"

#include <algorithm>
#include <format>
#include <iostream>
#include <string>
#include <string_view>

namespace Rpg::Tests {

constexpr std::string_view kReset = "\033[0m";
constexpr std::string_view kGreen = "\033[32m";
constexpr std::string_view kRed = "\033[31m";

std::string formatAttribute(int base, int effective, int width) {
  std::string result {std::format("{:>{}}/{:<{}}", effective, width, base, width)};

  if (const int delta {effective - base}; delta > 0) {
    result += std::format(" {}(+{}){}", kGreen, delta, kReset);
  } else if (delta < 0) {
    result += std::format(" {}({}){}", kRed, delta, kReset);
  }

  return result;
}

std::string healthBar(int effective, int current, int width) {
  const int filled {effective > 0 ? std::clamp(current * width / effective, 0, width) : 0};
  std::string bar(filled, '#');
  bar.append(width - filled, '-');
  const std::string_view color {current <= 0 || current < effective / 3 ? kRed : kGreen};

  return std::format("{}[{}]{}", color, bar, kReset);
}

void printCombatant(const Combatant& combatant) {
  std::cout << "#" << combatant.id().instanceId << " (TYPE " << combatant.id().typeId << ")\n"
            << "  HP  "
            << healthBar(combatant.health().effective(), combatant.health().current(), 20) << " "
            << combatant.health().current() << "/" << combatant.health().effective() << "\n"
            << "  STR "
            << formatAttribute(combatant.strength().base(), combatant.strength().effective(), 3)
            << "   "
            << "DEF "
            << formatAttribute(combatant.defense().base(), combatant.defense().effective(), 3)
            << "\n\n";
}

} // namespace Rpg::Tests

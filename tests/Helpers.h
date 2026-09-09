#pragma once

#include "Rpg/Entities/Character.h"
#include "Rpg/Entities/Enemy.h"

#include <iostream>

namespace Rpg::Tests
{

inline void printEntity(const Character& character)
{
  std::cout << "[" << "Protagonist" << "] "
          << "[ID] "  << character.id.instanceId << "/" << character.id.typeId << " "
          << "[HP] "  << character.health.current() << "/" << character.health.effective() << "/" << character.health.base() << " "
          << "[STR] " << character.strength.effective() << "/" << character.strength.base() << " "
          << "[DEF] " << character.defense.effective() << "/" << character.defense.base() << '\n';
}

inline void printEntity(const Enemy& enemy)
{
  std::cout << "[" << "Antagonist" << "] "
          << "[ID] "  << enemy.id.instanceId << "/" << enemy.id.typeId << " "
          << "[HP] "  << enemy.health.current() << "/" << enemy.health.effective() << "/" << enemy.health.base() << " "
          << "[STR] " << enemy.strength.effective() << "/" << enemy.strength.base() << " "
          << "[DEF] " << enemy.defense.effective() << "/" << enemy.defense.base() << '\n';
}

} // namespace Rpg::Tests

#pragma once

#include "Rpg/Systems/TurnManager.h"
#include "Rpg/Systems/SystemType.h"

namespace Rpg {

class TurnSystem {
public:
  explicit TurnSystem(TurnManager& turnManager);

  static constexpr SystemType type() {
    return SystemType::Turn;
  }

  void startTurn();
  void endTurn();

private:
  TurnManager& m_turnManager;
};

} // namespace Rpg

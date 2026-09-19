#pragma once

#include "Folio/Systems/SystemType.h"
#include "Folio/Systems/TurnManager.h"

namespace Folio {

class TurnSystem {
public:
  explicit TurnSystem(TurnManager& turnManager);

  static constexpr SystemType type() { return SystemType::Turn; }

  void startTurn();
  void endTurn();

private:
  TurnManager& m_turnManager;
};

} // namespace Folio

#include "Rpg/Systems/TurnSystem.h"

namespace Rpg {

TurnSystem::TurnSystem(TurnManager& turnManager) : m_turnManager {turnManager} {}

void TurnSystem::startTurn() {
  auto currentParticipant {m_turnManager.currentParticipant()};
}

void TurnSystem::endTurn() {
  m_turnManager.advance();
  startTurn();
}

} // namespace Rpg

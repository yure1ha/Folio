#include "Rpg/Systems/TurnManager.h"

#include "Rpg/Entities/Combatant.h"
#include "Rpg/Components/IdComponent.h"

#include <algorithm>
#include <utility>
#include <vector>

namespace Rpg {

void TurnManager::initialize(IdComponent playerId, TurnList participants) {
  m_playerId = playerId;
  m_turnList = std::move(participants);
}

void TurnManager::reset() {
  m_turnList.clear();
}

void TurnManager::add(IdComponent combatantId) {
  m_turnList.push_back(combatantId);
}

void TurnManager::remove(IdComponent combatantId) {
  std::erase_if(m_turnList, [combatantId](const auto& id) {
    return id == combatantId;
  });
}

void TurnManager::advance() {
  m_currentTurn++;
}

} // namespace Rpg

#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Core/Types.h"

#include <vector>

namespace Folio {

class TurnManager {
public:
  using TurnList = std::vector<IdComponent>;

  const TurnList& turnList() const { return m_turnList; }
  IdComponent currentParticipant() const { return m_turnList.at(m_currentTurn); }

  void initialize(IdComponent playerId, TurnList participants);
  void reset();
  void add(IdComponent combatantId);
  void remove(IdComponent combatantId);
  void advance();

private:
  TurnList m_turnList {};
  Turn m_currentTurn {};
  IdComponent m_playerId {};
};

} // namespace Folio

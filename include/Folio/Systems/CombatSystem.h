#pragma once

#include "Folio/Components/DefenseComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StrengthComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Events/EApplyDamage.h"
#include "Folio/Events/ECharacterDefeated.h"
#include "Folio/Events/EEnemyDefeated.h"
#include "Folio/Events/EHealthChanged.h"
#include "Folio/Systems/EntityManager.h"
#include "Folio/Systems/SystemType.h"

namespace Folio {

class CombatSystem {
public:
  CombatSystem(EntityManager& entityManager, EApplyDamageManager& damageEventManager,
               EHealthChangedManager& healthChangedManager,
               ECharacterDefeatedManager& characterDefeatedManager,
               EEnemyDefeatedManager& enemyDefeatedManager);

  ~CombatSystem();

  CombatSystem(const CombatSystem&) = delete;
  CombatSystem& operator=(const CombatSystem&) = delete;

  CombatSystem(CombatSystem&&) noexcept = delete;
  CombatSystem& operator=(CombatSystem&&) noexcept = delete;

  static constexpr SystemType type() { return SystemType::Combat; }

  static Damage calculateDamage(StrengthComponent str, DefenseComponent def);
  void applyDamage(IdComponent sourceId, IdComponent targetId) const;

private:
  static constexpr Strength kStrengthMultiplier {2};

  void onApplyDamage(const EApplyDamage& event) const;

  EntityManager& m_entityManager;
  EApplyDamageManager& m_damageEventManager;
  EHealthChangedManager& m_healthChangedManager;
  ECharacterDefeatedManager& m_characterDefeatedManager;
  EEnemyDefeatedManager& m_enemyDefeatedManager;
};

} // namespace Folio

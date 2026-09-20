#include "Folio/Systems/CombatSystem.h"

#include "Folio/Components/DefenseComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StrengthComponent.h"
#include "Folio/Core/Types.h"
#include "Folio/Entities/Character.h"
#include "Folio/Entities/Combatant.h"
#include "Folio/Entities/Enemy.h"
#include "Folio/Events/EApplyDamage.h"
#include "Folio/Events/ECharacterDefeated.h"
#include "Folio/Events/EEnemyDefeated.h"
#include "Folio/Events/EHealthChanged.h"
#include "Folio/Systems/EntityManager.h"
#include "Folio/Systems/EventManager.h"

namespace Folio {

CombatSystem::CombatSystem(EntityManager& entityManager, EApplyDamageManager& damageEventManager,
                           EHealthChangedManager& healthChangedManager,
                           ECharacterDefeatedManager& characterDefeatedManager,
                           EEnemyDefeatedManager& enemyDefeatedManager)
    : m_entityManager {entityManager}, m_damageEventManager {damageEventManager},
      m_healthChangedManager {healthChangedManager},
      m_characterDefeatedManager {characterDefeatedManager},
      m_enemyDefeatedManager {enemyDefeatedManager} {
  m_damageEventManager.subscribe(type(), [this](const EApplyDamage& event) {
    onApplyDamage(event);
  });
}

CombatSystem::~CombatSystem() {
  m_damageEventManager.unsubscribe(type());
}

Damage CombatSystem::calculateDamage(StrengthComponent str, DefenseComponent def) {
  return kStrengthMultiplier * str.effective() - def.effective();
}

void CombatSystem::applyDamage(IdComponent sourceId, IdComponent targetId) const {
  auto source {m_entityManager.find<Combatant>(sourceId)};
  auto target {m_entityManager.find<Combatant>(targetId)};

  if (!source || !target || !source->health().alive() || !target->health().alive()) return;

  const auto damage {calculateDamage(source->strength(), target->defense())};
  target->takeDamage(damage);

  m_healthChangedManager.dispatch(EHealthChanged {.sourceId = sourceId, .targetId = targetId});
}

void CombatSystem::onApplyDamage(const EApplyDamage& event) const {
  applyDamage(event.sourceId, event.targetId);
}

} // namespace Folio

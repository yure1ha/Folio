#include "Rpg/Systems/CombatSystem.h"

#include "Rpg/Systems/EntityManager.h"
#include "Rpg/Systems/EventManager.h"
#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Events/ApplyDamageEvent.h"

namespace Rpg {

CombatSystem::CombatSystem(EntityManager& entityManager, DamageEventManager& damageEventManager)
    : m_entityManager {entityManager}, m_damageEventManager {damageEventManager} {
  m_damageEventManager.subscribe(type(), [this](const ApplyDamageEvent& event) {
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

  const auto damage {calculateDamage(source->strength(), target->defense())};
  target->takeDamage(damage);
}

void CombatSystem::onApplyDamage(const ApplyDamageEvent& event) const {
  applyDamage(event.sourceId, event.targetId);
}

} // namespace Rpg

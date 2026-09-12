#include "Rpg/Systems/StatusModifierSystem.h"

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Entities/EntityManager.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Events/EventManager.h"
#include "Rpg/Events/RemoveStatusModifierEvent.h"
#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Modifiers/StatusModifierType.h"

namespace Rpg {

StatusModifierSystem::StatusModifierSystem(EntityManager& entityManager,
                                           ApplyStatusModifierEventManager& eventManager,
                                           RemoveStatusModifierEventManager& removeModifierManager)
    : m_entityManager {entityManager}, m_applyModifierManager {eventManager},
      m_removeModifierManager {removeModifierManager} {
  m_applyModifierManager.subscribe(type(), [this](const ApplyStatusModifierEvent& event) {
    onApplyStatusModifier(event);
  });

  m_removeModifierManager.subscribe(type(), [this](const RemoveStatusModifierEvent& event) {
    onRemoveStatusModifier(event);
  });
}

StatusModifierSystem::~StatusModifierSystem() {
  m_applyModifierManager.unsubscribe(type());
  m_removeModifierManager.unsubscribe(type());
}

void StatusModifierSystem::addModifier(const StatusModifier& modifier, IdComponent targetId) const {
  if (modifier.type == StatusModifierType::None) return;
  m_applyModifierManager.dispatch(
      ApplyStatusModifierEvent {.modifier = modifier, .targetId = targetId});
}

void StatusModifierSystem::removeModifier(IdComponent modifierId, IdComponent targetId) const {
  m_removeModifierManager.dispatch(
      RemoveStatusModifierEvent {.modifierId = modifierId, .targetId = targetId});
}

void StatusModifierSystem::onApplyStatusModifier(const ApplyStatusModifierEvent& event) const {
  auto target {m_entityManager.find<Combatant>(event.targetId)};
  if (!target) return;

  target->modifiers().add(event.modifier);
  updateModifiers(*target);
}

void StatusModifierSystem::onRemoveStatusModifier(const RemoveStatusModifierEvent& event) const {
  auto target {m_entityManager.find<Combatant>(event.targetId)};
  if (!target) return;

  target->modifiers().remove(event.modifierId);
  updateModifiers(*target);
}
} // namespace Rpg

#include "Rpg/Systems/ModifierSystem.h"

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Events/ApplyInstantModifierEvent.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Events/RemoveStatusModifierEvent.h"
#include "Rpg/Modifiers/InstantModifier.h"
#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Systems/EntityManager.h"
#include "Rpg/Systems/EventManager.h"

namespace Rpg {

ModifierSystem::ModifierSystem(EntityManager& entityManager,
                               ApplyStatusModifierEventManager& eventManager,
                               RemoveStatusModifierEventManager& removeModifierManager,
                               ApplyInstantModifierEventManager& applyInstantModifierManager)
    : m_entityManager {entityManager}, m_applyStatusModifierManager {eventManager},
      m_removeStatusModifierManager {removeModifierManager},
      m_applyInstantModifierManager {applyInstantModifierManager} {
  m_applyStatusModifierManager.subscribe(type(), [this](const ApplyStatusModifierEvent& event) {
    onApplyStatusModifier(event);
  });

  m_removeStatusModifierManager.subscribe(type(), [this](const RemoveStatusModifierEvent& event) {
    onRemoveStatusModifier(event);
  });

  m_applyInstantModifierManager.subscribe(type(), [this](const ApplyInstantModifierEvent& event) {
    onApplyInstantModifier(event);
  });
}

ModifierSystem::~ModifierSystem() {
  m_applyStatusModifierManager.unsubscribe(type());
  m_removeStatusModifierManager.unsubscribe(type());
  m_applyInstantModifierManager.unsubscribe(type());
}

void ModifierSystem::addStatusModifier(const StatusModifier& modifier, IdComponent targetId) const {
  m_applyStatusModifierManager.dispatch(
      ApplyStatusModifierEvent {.modifier = modifier, .targetId = targetId});
}

void ModifierSystem::removeStatusModifier(IdComponent modifierId, IdComponent targetId) const {
  m_removeStatusModifierManager.dispatch(
      RemoveStatusModifierEvent {.modifierId = modifierId, .targetId = targetId});
}

void ModifierSystem::applyInstantModifier(const InstantModifier& modifier,
                                          IdComponent targetId) const {
  m_applyInstantModifierManager.dispatch(
      ApplyInstantModifierEvent {.modifier = modifier, .targetId = targetId});
}

void ModifierSystem::onApplyStatusModifier(const ApplyStatusModifierEvent& event) const {
  auto target {m_entityManager.find<Combatant>(event.targetId)};
  if (!target) return;

  target->addStatusModifier(event.modifier);
}

void ModifierSystem::onRemoveStatusModifier(const RemoveStatusModifierEvent& event) const {
  auto target {m_entityManager.find<Combatant>(event.targetId)};
  if (!target) return;

  target->removeStatusModifier(event.modifierId);
}

void ModifierSystem::onApplyInstantModifier(const ApplyInstantModifierEvent& event) const {
  auto target {m_entityManager.find<Combatant>(event.targetId)};
  if (!target) return;

  target->applyInstanceModifier(event.modifier);
}

} // namespace Rpg

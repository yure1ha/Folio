#include "Folio/Systems/ModifierSystem.h"

#include "Folio/Components/IdComponent.h"
#include "Folio/Entities/Combatant.h"
#include "Folio/Events/EApplyInstantModifier.h"
#include "Folio/Events/EApplyStatusModifier.h"
#include "Folio/Events/EHealthChanged.h"
#include "Folio/Events/ERemoveStatusModifier.h"
#include "Folio/Modifiers/InstantModifier.h"
#include "Folio/Modifiers/StatusModifier.h"
#include "Folio/Systems/EntityManager.h"
#include "Folio/Systems/EventManager.h"

namespace Folio {

ModifierSystem::ModifierSystem(EntityManager& entityManager,
                               EApplyStatusModifierManager& applyStatusModifierEventManager,
                               ERemoveStatusModifierManager& removeStatusModifierManager,
                               EApplyInstantModifierManager& applyInstantModifierManager,
                               EHealthChangedManager& healthChangedManager)
    : m_entityManager {entityManager},
      m_applyStatusModifierManager {applyStatusModifierEventManager},
      m_removeStatusModifierManager {removeStatusModifierManager},
      m_applyInstantModifierManager {applyInstantModifierManager},
      m_healthChangedManager {healthChangedManager} {
  m_applyStatusModifierManager.subscribe(type(), [this](const EApplyStatusModifier& event) {
    onApplyStatusModifier(event);
  });

  m_removeStatusModifierManager.subscribe(type(), [this](const ERemoveStatusModifier& event) {
    onRemoveStatusModifier(event);
  });

  m_applyInstantModifierManager.subscribe(type(), [this](const EApplyInstantModifier& event) {
    onApplyInstantModifier(event);
  });
}

ModifierSystem::~ModifierSystem() {
  m_applyStatusModifierManager.unsubscribe(type());
  m_removeStatusModifierManager.unsubscribe(type());
  m_applyInstantModifierManager.unsubscribe(type());
}

void ModifierSystem::addStatusModifier(const StatusModifier& modifier, IdComponent sourceId,
                                       IdComponent targetId) const {
  m_applyStatusModifierManager.dispatch(
      EApplyStatusModifier {.modifier = modifier, .sourceId = sourceId, .targetId = targetId});
}

void ModifierSystem::removeStatusModifier(IdComponent modifierId, IdComponent targetId) const {
  m_removeStatusModifierManager.dispatch(
      ERemoveStatusModifier {.modifierId = modifierId, .targetId = targetId});
}

void ModifierSystem::applyInstantModifier(const InstantModifier& modifier, IdComponent sourceId,
                                          IdComponent targetId) const {
  m_applyInstantModifierManager.dispatch(
      EApplyInstantModifier {.modifier = modifier, .sourceId = sourceId, .targetId = targetId});
}

void ModifierSystem::onApplyStatusModifier(const EApplyStatusModifier& event) const {
  auto target {m_entityManager.find<Combatant>(event.targetId)};
  if (!target) return;

  target->addStatusModifier(event.modifier);
}

void ModifierSystem::onRemoveStatusModifier(const ERemoveStatusModifier& event) const {
  auto target {m_entityManager.find<Combatant>(event.targetId)};
  if (!target) return;

  target->removeStatusModifier(event.modifierId);
}

void ModifierSystem::onApplyInstantModifier(const EApplyInstantModifier& event) const {
  auto target {m_entityManager.find<Combatant>(event.targetId)};
  if (!target) return;

  target->applyInstanceModifier(event.modifier);

  m_healthChangedManager.dispatch(
      EHealthChanged {.sourceId = event.sourceId, .targetId = event.targetId});
}

} // namespace Folio

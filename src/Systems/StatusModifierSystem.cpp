#include "Rpg/Systems/StatusModifierSystem.h"

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Entities/EntityManager.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Events/EventManager.h"
#include "Rpg/Modifiers/StatusModifier.h"

namespace Rpg {

StatusModifierSystem::StatusModifierSystem(EntityManager& entityManager,
                                           ModifierEventManager& eventManager)
    : m_entityManager {entityManager}, m_modifierEventManager {eventManager} {
    m_modifierEventManager.subscribe(SystemType::StatusModifier,
                                     [this](const ApplyStatusModifierEvent& event) {
                                         onApplyStatusModifier(event);
                                     });
}

StatusModifierSystem::~StatusModifierSystem() {
    m_modifierEventManager.unsubscribe(SystemType::StatusModifier);
}

void StatusModifierSystem::addModifier(const StatusModifier& modifier, InstanceId targetId) const {
    const ApplyStatusModifierEvent event {.modifier = modifier, .targetId = targetId};
    m_modifierEventManager.dispatch(event);
}

void StatusModifierSystem::removeModifier(const StatusModifier& modifier,
                                          InstanceId targetId) const {
    auto target {m_entityManager.find<Combatant>(targetId)};
    target->modifiers().remove(modifier.id);
}

void StatusModifierSystem::onApplyStatusModifier(const ApplyStatusModifierEvent& event) const {
    auto target {m_entityManager.find<Combatant>(event.targetId)};
    if (!target) return;

    target->modifiers().add(event.modifier);
    updateModifiers(*target);
}

} // namespace Rpg

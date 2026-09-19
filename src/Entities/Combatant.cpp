#include "Folio/Entities/Combatant.h"

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Components/DefenseComponent.h"
#include "Folio/Components/HealthComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StrengthComponent.h"
#include "Folio/Entities/Entity.h"
#include "Folio/Modifiers/InstantModifierType.h"
#include "Folio/Modifiers/StatusModifier.h"

#include <utility>

namespace Folio {

Combatant::Combatant(IdComponent id, HealthComponent health, StrengthComponent strength,
                     DefenseComponent defense, ModifierList modifiers)
    : Entity {id}, m_health {health}, m_strength {strength}, m_defense {defense},
      m_modifiers {std::move(modifiers)} {}

void Combatant::addStatusModifier(const StatusModifier& modifier) {
  m_modifiers.add(modifier);
  refreshStatusModifiers();
}

void Combatant::removeStatusModifier(IdComponent modifierId) {
  m_modifiers.remove(modifierId);
  refreshStatusModifiers();
}

void Combatant::applyInstanceModifier(const InstantModifier& modifier) {
  switch (modifier.type) {
  case InstantModifierType::None:
    break;

  case InstantModifierType::Heal:
    m_health.heal(modifier.value);
    break;

  case InstantModifierType::Damage:
    m_health.takeDamage(modifier.value);
    break;
  }
}

void Combatant::refreshStatusModifiers() {
  m_health.reset();
  m_strength.reset();
  m_defense.reset();

  for (const auto& modifier : m_modifiers) {
    applyStatusModifier(modifier, m_health);
    applyStatusModifier(modifier, m_strength);
    applyStatusModifier(modifier, m_defense);
  }
}

} // namespace Folio

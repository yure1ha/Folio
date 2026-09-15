#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/HealthComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Concepts/AttributeComponent.h"
#include "Rpg/Entities/Entity.h"
#include "Rpg/Modifiers/InstantModifier.h"
#include "Rpg/Modifiers/StatusModifier.h"

namespace Rpg {

class Combatant : public Entity {
public:
  using ModifierList = ContainerComponent<StatusModifier>;

  Combatant(IdComponent id, HealthComponent health, StrengthComponent strength,
            DefenseComponent defense, ModifierList modifiers);

  HealthComponent health() const {
    return m_health;
  }

  StrengthComponent strength() const {
    return m_strength;
  }

  DefenseComponent defense() const {
    return m_defense;
  }

  const ModifierList& modifiers() const {
    return m_modifiers;
  }

  void heal(Health delta) {
    m_health.heal(delta);
  }

  void takeDamage(Health delta) {
    m_health.takeDamage(delta);
  }

  void healFull() {
    m_health.healFull();
  }

  void addStatusModifier(const StatusModifier& modifier);
  void removeStatusModifier(IdComponent modifierId);
  void applyInstanceModifier(const InstantModifier& modifier);

private:
  template <Concepts::AttributeComponent T>
  static void applyStatusModifier(const StatusModifier& modifier, T& attr) {
    if (!modifier.active() || modifier.type != T::type()) return;

    if (const auto total {modifier.total()}; total > 0) {
      attr.increase(total);
    } else if (total < 0) {
      attr.decrease(-total);
    }
  }

  void refreshStatusModifiers();

  HealthComponent m_health;
  StrengthComponent m_strength;
  DefenseComponent m_defense;
  ModifierList m_modifiers;
};

} // namespace Rpg

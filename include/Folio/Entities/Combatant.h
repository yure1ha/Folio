#pragma once

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Components/DefenseComponent.h"
#include "Folio/Components/HealthComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Components/StrengthComponent.h"
#include "Folio/Components/ValueComponent.h"
#include "Folio/Concepts/AttributeComponent.h"
#include "Folio/Entities/Entity.h"
#include "Folio/Modifiers/InstantModifier.h"
#include "Folio/Modifiers/StatusModifier.h"

namespace Folio {

class Combatant : public Entity {
public:
  using ModifierList = ContainerComponent<StatusModifier>;

  Combatant(IdComponent id, ValueComponent exp, HealthComponent health, StrengthComponent strength,
            DefenseComponent defense, ModifierList modifiers);

  ValueComponent exp() const { return m_exp; }
  HealthComponent health() const { return m_health; }
  StrengthComponent strength() const { return m_strength; }
  DefenseComponent defense() const { return m_defense; }
  const ModifierList& modifiers() const { return m_modifiers; }

  void heal(Health delta) { m_health.heal(delta); }
  void takeDamage(Health delta) { m_health.takeDamage(delta); }
  void healFull() { m_health.healFull(); }

  void increaseExp(Experience delta);
  void decreaseExp(Experience delta);

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

  ValueComponent m_exp;
  HealthComponent m_health;
  StrengthComponent m_strength;
  DefenseComponent m_defense;
  ModifierList m_modifiers;
};

} // namespace Folio

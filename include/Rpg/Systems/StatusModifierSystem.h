#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Concepts/AttributeComponent.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Entities/EntityManager.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Events/RemoveStatusModifierEvent.h"
#include "Rpg/Modifiers/StatusModifier.h"

namespace Rpg {

class StatusModifierSystem {
public:
  using ModifierList = ContainerComponent<StatusModifier>;

  StatusModifierSystem(EntityManager& entityManager, ApplyStatusModifierEventManager& eventManager,
                       RemoveStatusModifierEventManager& removeModifierManager);

  ~StatusModifierSystem();

  StatusModifierSystem(const StatusModifierSystem&) = delete;
  StatusModifierSystem& operator=(const StatusModifierSystem&) = delete;

  StatusModifierSystem(StatusModifierSystem&&) noexcept = delete;
  StatusModifierSystem& operator=(StatusModifierSystem&&) noexcept = delete;

  static constexpr SystemType type() {
    return SystemType::StatusModifier;
  }

  void addModifier(const StatusModifier& modifier, IdComponent targetId) const;
  void removeModifier(IdComponent modifierId, IdComponent targetId) const;

  template <Concepts::AttributeComponent T>
  static void applyModifier(const StatusModifier& modifier, T& attr) {
    if (!modifier.isActive() || modifier.type != T::kModifierType) return;

    if (const auto total {modifier.total()}; total > 0) {
      attr.increase(total);
    }

    else if (total < 0) {
      attr.decrease(-total);
    }
  }

  static void updateModifiers(Combatant& target) {
    target.health().reset();
    target.strength().reset();
    target.defense().reset();

    for (const auto& modifier : target.modifiers()) {
      applyModifier(modifier, target.health());
      applyModifier(modifier, target.strength());
      applyModifier(modifier, target.defense());
    }
  }

private:
  void onApplyStatusModifier(const ApplyStatusModifierEvent& event) const;
  void onRemoveStatusModifier(const RemoveStatusModifierEvent& event) const;

  EntityManager& m_entityManager;
  ApplyStatusModifierEventManager& m_applyModifierManager;
  RemoveStatusModifierEventManager& m_removeModifierManager;
};

} // namespace Rpg

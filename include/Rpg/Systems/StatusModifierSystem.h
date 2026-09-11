#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Concepts/AttributeComponent.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Entities/EntityManager.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Modifiers/StatusModifier.h"

#include <cstdint>

namespace Rpg {

class StatusModifierSystem {
  public:
    using ModifierList = ContainerComponent<StatusModifier>;

    StatusModifierSystem(EntityManager& entityManager, ModifierEventManager& eventManager);
    ~StatusModifierSystem();

    StatusModifierSystem(const StatusModifierSystem&) = delete;
    StatusModifierSystem& operator=(const StatusModifierSystem&) = delete;

    StatusModifierSystem(StatusModifierSystem&&) noexcept = delete;
    StatusModifierSystem& operator=(StatusModifierSystem&&) noexcept = delete;

    void addModifier(const StatusModifier& modifier, InstanceId targetId) const;
    void removeModifier(const StatusModifier& modifier, InstanceId targetId) const;

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

    EntityManager& m_entityManager;
    ModifierEventManager& m_modifierEventManager;
};

} // namespace Rpg

#pragma once

#include "Rpg/Components/ContainerComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Events/ApplyInstantModifierEvent.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Events/RemoveStatusModifierEvent.h"
#include "Rpg/Modifiers/InstantModifier.h"
#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Systems/EntityManager.h"

namespace Rpg {

class ModifierSystem {
public:
  using ModifierList = ContainerComponent<StatusModifier>;

  ModifierSystem(EntityManager& entityManager, ApplyStatusModifierEventManager& eventManager,
                 RemoveStatusModifierEventManager& removeModifierManager,
                 ApplyInstantModifierEventManager& applyInstantModifierManager);

  ~ModifierSystem();

  ModifierSystem(const ModifierSystem&) = delete;
  ModifierSystem& operator=(const ModifierSystem&) = delete;

  ModifierSystem(ModifierSystem&&) noexcept = delete;
  ModifierSystem& operator=(ModifierSystem&&) noexcept = delete;

  static constexpr SystemType type() {
    return SystemType::StatusModifier;
  }

  void addStatusModifier(const StatusModifier& modifier, IdComponent sourceId,
                         IdComponent targetId) const;

  void removeStatusModifier(IdComponent modifierId, IdComponent targetId) const;

  void applyInstantModifier(const InstantModifier& modifier, IdComponent sourceId,
                            IdComponent targetId) const;

private:
  void onApplyStatusModifier(const ApplyStatusModifierEvent& event) const;
  void onRemoveStatusModifier(const RemoveStatusModifierEvent& event) const;
  void onApplyInstantModifier(const ApplyInstantModifierEvent& event) const;

  EntityManager& m_entityManager;
  ApplyStatusModifierEventManager& m_applyStatusModifierManager;
  RemoveStatusModifierEventManager& m_removeStatusModifierManager;
  ApplyInstantModifierEventManager& m_applyInstantModifierManager;
};

} // namespace Rpg

#pragma once

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Components/IdComponent.h"
#include "Folio/Events/EApplyInstantModifier.h"
#include "Folio/Events/EApplyStatusModifier.h"
#include "Folio/Events/EHealthChanged.h"
#include "Folio/Events/ERemoveStatusModifier.h"
#include "Folio/Modifiers/InstantModifier.h"
#include "Folio/Modifiers/StatusModifier.h"
#include "Folio/Systems/EntityManager.h"

namespace Folio {

class ModifierSystem {
public:
  using ModifierList = ContainerComponent<StatusModifier>;

  ModifierSystem(EntityManager& entityManager,
                 EApplyStatusModifierManager& applyStatusModifierEventManager,
                 ERemoveStatusModifierManager& removeStatusModifierManager,
                 EApplyInstantModifierManager& applyInstantModifierManager,
                 EHealthChangedManager& healthChangedManager);

  ~ModifierSystem();

  ModifierSystem(const ModifierSystem&) = delete;
  ModifierSystem& operator=(const ModifierSystem&) = delete;

  ModifierSystem(ModifierSystem&&) noexcept = delete;
  ModifierSystem& operator=(ModifierSystem&&) noexcept = delete;

  static constexpr SystemType type() { return SystemType::StatusModifier; }

  void addStatusModifier(const StatusModifier& modifier, IdComponent sourceId,
                         IdComponent targetId) const;

  void removeStatusModifier(IdComponent modifierId, IdComponent targetId) const;

  void applyInstantModifier(const InstantModifier& modifier, IdComponent sourceId,
                            IdComponent targetId) const;

private:
  void onApplyStatusModifier(const EApplyStatusModifier& event) const;
  void onRemoveStatusModifier(const ERemoveStatusModifier& event) const;
  void onApplyInstantModifier(const EApplyInstantModifier& event) const;

  EntityManager& m_entityManager;
  EApplyStatusModifierManager& m_applyStatusModifierManager;
  ERemoveStatusModifierManager& m_removeStatusModifierManager;
  EApplyInstantModifierManager& m_applyInstantModifierManager;
  EHealthChangedManager& m_healthChangedManager;
};

} // namespace Folio

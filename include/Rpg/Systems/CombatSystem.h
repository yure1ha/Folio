#pragma once

#include "EntityManager.h"
#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Core/Types.h"
#include "Rpg/Events/ApplyDamageEvent.h"
#include "Rpg/Systems/SystemType.h"

namespace Rpg {

class CombatSystem {
public:
  CombatSystem(EntityManager& entityManager, ApplyDamageEventManager& damageEventManager);

  ~CombatSystem();

  CombatSystem(const CombatSystem&) = delete;
  CombatSystem& operator=(const CombatSystem&) = delete;

  CombatSystem(CombatSystem&&) noexcept = delete;
  CombatSystem& operator=(CombatSystem&&) noexcept = delete;

  static constexpr SystemType type() {
    return SystemType::Combat;
  }

  static Damage calculateDamage(StrengthComponent str, DefenseComponent def);
  void applyDamage(IdComponent sourceId, IdComponent targetId) const;

private:
  static constexpr Strength kStrengthMultiplier {2};

  void onApplyDamage(const ApplyDamageEvent& event) const;

  EntityManager& m_entityManager;
  ApplyDamageEventManager& m_damageEventManager;
};

} // namespace Rpg

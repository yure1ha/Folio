#pragma once

#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Entities/Combatant.h"
#include "Rpg/Entities/EntityManager.h"
#include "Rpg/Events/ApplyDamageEvent.h"
#include "Rpg/Events/EventManager.h"

#include <cstdint>

namespace Rpg {

class CombatSystem {
  public:
    CombatSystem(EntityManager& entityManager, DamageEventManager& damageEventManager);
    ~CombatSystem();

    CombatSystem(const CombatSystem&) = delete;
    CombatSystem& operator=(const CombatSystem&) = delete;

    CombatSystem(CombatSystem&&) noexcept = delete;
    CombatSystem& operator=(CombatSystem&&) noexcept = delete;

    static std::int32_t calculateDamage(const StrengthComponent& str, const DefenseComponent& def);
    void applyDamage(InstanceId sourceId, InstanceId targetId) const;

  private:
    void onApplyDamage(const ApplyDamageEvent& event) const;

    EntityManager& m_entityManager;
    DamageEventManager& m_damageEventManager;
};

} // namespace Rpg

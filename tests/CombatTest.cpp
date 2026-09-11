#include "Helpers.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Entities/Character.h"
#include "Rpg/Entities/Enemy.h"
#include "Rpg/Entities/EntityManager.h"
#include "Rpg/Events/ApplyDamageEvent.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Events/EventManager.h"
#include "Rpg/Factories/IdFactory.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Modifiers/StatusModifierType.h"
#include "Rpg/Systems/CombatSystem.h"
#include "Rpg/Systems/InventorySystem.h"
#include "Rpg/Systems/StatusModifierSystem.h"

#include <memory>

namespace Rpg::Tests {

void runCombatTests() {
    IdFactory idFactory;

    StatusModifier healthUp {.id = {.typeId = 1000, .instanceId = idFactory.allocate()},
                             .type = StatusModifierType::Health,
                             .stack = {StackComponent {99, 1}},
                             .value = 10};

    StatusModifier healthDown {.id = {.typeId = 1001, .instanceId = idFactory.allocate()},
                               .type = StatusModifierType::Health,
                               .stack = {StackComponent {99, 1}},
                               .value = -10};

    StatusModifier strengthUp {.id = {.typeId = 1002, .instanceId = idFactory.allocate()},
                               .type = StatusModifierType::Strength,
                               .stack = {StackComponent {99, 1}},
                               .value = 10};

    StatusModifier strengthDown {.id = {.typeId = 1003, .instanceId = idFactory.allocate()},
                                 .type = StatusModifierType::Strength,
                                 .stack = {StackComponent {99, 1}},
                                 .value = -10};

    StatusModifier defenseUp {.id = {.typeId = 1004, .instanceId = idFactory.allocate()},
                              .type = StatusModifierType::Defense,
                              .stack = {StackComponent {99, 1}},
                              .value = 10};

    StatusModifier defenseDown {.id = {.typeId = 1005, .instanceId = idFactory.allocate()},
                                .type = StatusModifierType::Defense,
                                .stack = {StackComponent {99, 1}},
                                .value = -10};

    const Consumable consumable {
        .id = {.typeId = 100, .instanceId = idFactory.allocate()},
        .stack = {99, 10},
        .modifier = healthUp,
    };

    const Weapon weapon {
        .id = {.typeId = 101, .instanceId = idFactory.allocate()},
        .stack = {1, 1},
        .strength = {5, 5},
        .modifier = strengthUp,
    };

    const Armor armor {
        .id = {.typeId = 102, .instanceId = idFactory.allocate()},
        .stack = {1, 1},
        .defense = {5, 5},
        .modifier = defenseUp,
    };

    CharacterBlueprint protagonistBp {
        .typeId = 1,

        .baseHealth = 100,
        .effectiveHealth = 100,
        .currentHealth = 100,

        .baseStrength = 20,
        .effectiveStrength = 20,

        .baseDefense = 20,
        .effectiveDefense = 20,
    };

    EnemyBlueprint antagonistBp {
        .typeId = 2,

        .baseHealth = 100,
        .effectiveHealth = 100,
        .currentHealth = 100,

        .baseStrength = 50,
        .effectiveStrength = 50,

        .baseDefense = 30,
        .effectiveDefense = 30,
    };

    EntityManager entityManager {idFactory};

    auto protagonistPtr {std::make_unique<Character>(protagonistBp)};
    Character& protagonist {*protagonistPtr};
    entityManager.add(std::move(protagonistPtr));

    auto antagonistPtr {std::make_unique<Enemy>(antagonistBp)};
    Enemy& antagonist {*antagonistPtr};
    entityManager.add(std::move(antagonistPtr));

    printCombatant(protagonist);
    printCombatant(antagonist);

    EventManager<ApplyStatusModifierEvent> modifierEventManager;
    StatusModifierSystem statusModifierSystem {entityManager, modifierEventManager};

    EventManager<ApplyDamageEvent> damageEventManager;
    CombatSystem combatSystem {entityManager, damageEventManager};

    InventorySystem inventorySystem {entityManager, modifierEventManager};

    inventorySystem.addItem(weapon, protagonist.weapons());
    inventorySystem.addItem(armor, protagonist.armor());
    inventorySystem.equipWeapon(weapon, protagonist.id().instanceId);
    inventorySystem.equipArmor(armor, protagonist.id().instanceId);
    printCombatant(protagonist);

    combatSystem.applyDamage(antagonist.id().instanceId, protagonist.id().instanceId);
    printCombatant(protagonist);

    statusModifierSystem.addModifier(defenseDown, antagonist.id().instanceId);
    combatSystem.applyDamage(protagonist.id().instanceId, antagonist.id().instanceId);
    printCombatant(antagonist);

    combatSystem.applyDamage(antagonist.id().instanceId, protagonist.id().instanceId);
    printCombatant(protagonist);

    protagonist.health().heal(100);
    printCombatant(protagonist);

    antagonist.health().takeDamage(100);
    printCombatant(antagonist);

    inventorySystem.addItem(consumable, protagonist.consumables());
    inventorySystem.useConsumable(consumable, protagonist.id().instanceId);
    printCombatant(protagonist);

    protagonist.health().reset();
    protagonist.strength().reset();
    protagonist.defense().reset();
    printCombatant(protagonist);
}

} // namespace Rpg::Tests

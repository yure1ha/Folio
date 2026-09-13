#include "Rpg/Systems/EntityManager.h"
#include "Rpg/Systems/EventManager.h"
#include "Helpers.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Entities/Character.h"
#include "Rpg/Entities/Enemy.h"
#include "Rpg/Events/ApplyDamageEvent.h"
#include "Rpg/Events/ApplyStatusModifierEvent.h"
#include "Rpg/Events/RemoveStatusModifierEvent.h"
#include "Rpg/Factories/EntityFactory.h"
#include "Rpg/Factories/IdFactory.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Modifiers/StatusModifierType.h"
#include "Rpg/Systems/CombatSystem.h"
#include "Rpg/Systems/InventorySystem.h"
#include "Rpg/Systems/ModifierSystem.h"

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
      .statusModifier = healthUp,
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

  EntityManager entityManager;
  EntityFactory entityFactory {idFactory, entityManager};

  auto protagonistId {entityFactory.create(protagonistBp)};
  auto antagonistId {entityFactory.create(antagonistBp)};

  auto protagonistPtr {entityManager.find<Character>(protagonistId)};
  auto antagonistPtr {entityManager.find<Enemy>(antagonistId)};

  Character& protagonist {*protagonistPtr};
  Enemy& antagonist {*antagonistPtr};

  printCombatant(protagonist);
  printCombatant(antagonist);

  EventManager<ApplyStatusModifierEvent> applyModifierManager;
  EventManager<RemoveStatusModifierEvent> removeModifierManager;
  ModifierSystem statusModifierSystem {entityManager, applyModifierManager,
                                             removeModifierManager};

  EventManager<ApplyDamageEvent> damageEventManager;
  CombatSystem combatSystem {entityManager, damageEventManager};

  InventorySystem inventorySystem {entityManager, statusModifierSystem};

  inventorySystem.addItem(weapon, protagonist.weapons());
  inventorySystem.addItem(armor, protagonist.armor());
  inventorySystem.equipWeapon(weapon, protagonist.id());
  inventorySystem.equipArmor(armor, protagonist.id());
  printCombatant(protagonist);

  combatSystem.applyDamage(antagonist.id(), protagonist.id());
  printCombatant(protagonist);

  statusModifierSystem.addStatusModifier(defenseDown, antagonist.id());
  combatSystem.applyDamage(protagonist.id(), antagonist.id());
  printCombatant(antagonist);

  combatSystem.applyDamage(antagonist.id(), protagonist.id());
  printCombatant(protagonist);

  protagonist.health().heal(100);
  printCombatant(protagonist);

  antagonist.health().takeDamage(100);
  printCombatant(antagonist);

  inventorySystem.addItem(consumable, protagonist.consumables());
  inventorySystem.useConsumable(consumable, protagonist.id());
  printCombatant(protagonist);

  protagonist.health().reset();
  protagonist.strength().reset();
  protagonist.defense().reset();
  printCombatant(protagonist);
}

} // namespace Rpg::Tests

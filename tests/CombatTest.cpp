#include "Folio/Components/StackComponent.h"
#include "Folio/Entities/Character.h"
#include "Folio/Entities/Enemy.h"
#include "Folio/Events/EApplyDamage.h"
#include "Folio/Events/EApplyInstantModifier.h"
#include "Folio/Events/EApplyStatusModifier.h"
#include "Folio/Events/ECharacterDefeated.h"
#include "Folio/Events/EEnemyDefeated.h"
#include "Folio/Events/EHealthChanged.h"
#include "Folio/Events/ERemoveStatusModifier.h"
#include "Folio/Factories/EntityFactory.h"
#include "Folio/Factories/IdFactory.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Consumable.h"
#include "Folio/Items/Weapon.h"
#include "Folio/Modifiers/InstantModifier.h"
#include "Folio/Modifiers/InstantModifierType.h"
#include "Folio/Modifiers/StatusModifier.h"
#include "Folio/Modifiers/StatusModifierType.h"
#include "Folio/Systems/CombatSystem.h"
#include "Folio/Systems/EntityManager.h"
#include "Folio/Systems/EventManager.h"
#include "Folio/Systems/InventorySystem.h"
#include "Folio/Systems/ModifierSystem.h"
#include "Utilities.h"

namespace Folio::Tests {

void runCombatTests() {
  IdFactory idFactory;

  // Initialize Status Modifiers
  StatusModifier healthUp {.id = {.typeId = 1000, .instanceId = idFactory.allocate()},
                           .type = StatusModifierType::Health,
                           .stack = {StackComponent {99, 1}},
                           .value = {.base = 10}};

  StatusModifier healthDown {.id = {.typeId = 1001, .instanceId = idFactory.allocate()},
                             .type = StatusModifierType::Health,
                             .stack = {StackComponent {99, 1}},
                             .value = {.base = -10}};

  StatusModifier strengthUp {.id = {.typeId = 1002, .instanceId = idFactory.allocate()},
                             .type = StatusModifierType::Strength,
                             .stack = {StackComponent {99, 1}},
                             .value = {.base = 5}};

  StatusModifier strengthDown {.id = {.typeId = 1003, .instanceId = idFactory.allocate()},
                               .type = StatusModifierType::Strength,
                               .stack = {StackComponent {99, 1}},
                               .value = {.base = -5}};

  StatusModifier defenseUp {.id = {.typeId = 1004, .instanceId = idFactory.allocate()},
                            .type = StatusModifierType::Defense,
                            .stack = {StackComponent {99, 1}},
                            .value = {.base = 5}};

  StatusModifier defenseDown {.id = {.typeId = 1005, .instanceId = idFactory.allocate()},
                              .type = StatusModifierType::Defense,
                              .stack = {StackComponent {99, 1}},
                              .value = {.base = -5}};

  InstantModifier heal {
      .id = {.typeId = 1006, .instanceId = idFactory.allocate()},
      .type = InstantModifierType::Heal,
      .value = 10,
  };

  InstantModifier damage {
      .id = {.typeId = 1007, .instanceId = idFactory.allocate()},
      .type = InstantModifierType::Damage,
      .value = 10,
  };

  // Initialize Items
  const Consumable consumable {
      .id = {.typeId = 100, .instanceId = idFactory.allocate()},
      .stack = {99, 10},
      .statusModifier = healthUp,
      .instantModifier = heal,
  };

  const Weapon weapon {
      .stack = {1, 1},
      .strength = {5, 5},
      .modifier = strengthUp,
  };

  const Armor armor {
      .stack = {1, 1},
      .defense = {4, 4},
      .modifier = defenseUp,
  };

  const Consumable shuriken {
      .id = {.typeId = 103, .instanceId = idFactory.allocate()},
      .stack = {99, 1},
      .instantModifier = damage,
  };

  CharacterBlueprint protagonistBp {
      .typeId = 1,
      .baseHealth = 100,
      .effectiveHealth = 100,
      .currentHealth = 100,
      .baseStrength = 25,
      .effectiveStrength = 25,
      .baseDefense = 25,
      .effectiveDefense = 25,
  };

  EnemyBlueprint antagonistBp {
      .typeId = 2,
      .baseHealth = 300,
      .effectiveHealth = 300,
      .currentHealth = 300,
      .baseStrength = 30,
      .effectiveStrength = 30,
      .baseDefense = 20,
      .effectiveDefense = 20,
  };

  // Initialize Systems
  EApplyStatusModifierManager applyStatusModifierManager;
  ERemoveStatusModifierManager removeStatusModifierManager;
  EApplyInstantModifierManager applyInstantModifierManager;
  EApplyDamageManager damageManager;
  EHealthChangedManager healthChangedManager;
  ECharacterDefeatedManager characterDefeatedManager;
  EEnemyDefeatedManager enemyDefeatedManager;

  EntityManager entityManager {idFactory, healthChangedManager, characterDefeatedManager,
                               enemyDefeatedManager};
  ModifierSystem modifierSystem {entityManager, applyStatusModifierManager,
                                 removeStatusModifierManager, applyInstantModifierManager,
                                 healthChangedManager};
  CombatSystem combatSystem {entityManager, damageManager, healthChangedManager,
                             characterDefeatedManager, enemyDefeatedManager};
  InventorySystem inventorySystem {entityManager, modifierSystem};

  // Initialize Entities
  EntityFactory entityFactory {idFactory, entityManager};
  auto protagonistId {entityFactory.create(protagonistBp)};
  auto antagonistId {entityFactory.create(antagonistBp)};

  auto protagonistPtr {entityManager.find<Character>(protagonistId)};
  auto antagonistPtr {entityManager.find<Enemy>(antagonistId)};

  Character& protagonist {*protagonistPtr};
  Enemy& antagonist {*antagonistPtr};

  // Start Test
  printCombatant(protagonist);
  printCombatant(antagonist);

  // Phase 1
  protagonist.addItem(weapon);
  protagonist.addItem(armor);
  inventorySystem.equipWeapon(weapon.id, protagonistId);
  inventorySystem.equipArmor(armor.id, protagonistId);
  printCombatant(protagonist);

  // Phase 2
  combatSystem.applyDamage(protagonistId, antagonistId);
  combatSystem.applyDamage(antagonistId, protagonistId);
  printCombatant(protagonist);
  printCombatant(antagonist);

  // Phase 3
  modifierSystem.addStatusModifier(defenseDown, protagonistId, antagonistId);
  modifierSystem.addStatusModifier(strengthDown, protagonistId, antagonistId);
  combatSystem.applyDamage(protagonistId, antagonistId);
  combatSystem.applyDamage(antagonistId, protagonistId);
  printCombatant(protagonist);
  printCombatant(antagonist);

  // Phase 4
  modifierSystem.addStatusModifier(defenseUp, antagonistId, antagonistId);
  modifierSystem.addStatusModifier(defenseDown, antagonistId, protagonistId);
  combatSystem.applyDamage(antagonistId, protagonistId);
  combatSystem.applyDamage(protagonistId, antagonistId);
  printCombatant(protagonist);
  printCombatant(antagonist);

  // Phase 5
  protagonist.addItem(consumable);
  protagonist.addItem(shuriken);
  inventorySystem.useConsumable(consumable.id, protagonistId, protagonistId);
  inventorySystem.useConsumable(shuriken.id, protagonistId, antagonistId);
  printCombatant(protagonist);
  printCombatant(antagonist);

  // Phase 6
  modifierSystem.addStatusModifier(healthDown, protagonistId, antagonistId);
  printCombatant(antagonist);

  // Phase 7
  modifierSystem.addStatusModifier(strengthUp, protagonistId, protagonistId);
  combatSystem.applyDamage(protagonistId, antagonistId);
  combatSystem.applyDamage(antagonistId, protagonistId);
  printCombatant(protagonist);
  printCombatant(antagonist);

  // Phase 8
  modifierSystem.addStatusModifier(healthUp, antagonistId, antagonistId);
  printCombatant(antagonist);

  // Phase 9
  inventorySystem.useConsumable(consumable.id, protagonistId, protagonistId);
  inventorySystem.useConsumable(shuriken.id, protagonistId, antagonistId);
  combatSystem.applyDamage(protagonistId, antagonistId);
  combatSystem.applyDamage(antagonistId, protagonistId);
  printCombatant(protagonist);
  printCombatant(antagonist);

  // Phase 10
  inventorySystem.useConsumable(shuriken.id, protagonistId, antagonistId);

  while (antagonist.health().alive()) {
    combatSystem.applyDamage(protagonistId, antagonistId);
  }

  printCombatant(protagonist);
  printCombatant(antagonist);

  entityManager.clearDestructionQueue();
}

} // namespace Folio::Tests

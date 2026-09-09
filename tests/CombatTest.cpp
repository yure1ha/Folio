#include "Helpers.h"

#include "Rpg/Factories/IdFactory.h"

#include "Rpg/Components/StackComponent.h"

#include "Rpg/Modifiers/StatusModifier.h"
#include "Rpg/Modifiers/StatusModifierType.h"

#include "Rpg/Items/Armor.h"
#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"

#include "Rpg/Entities/Character.h"
#include "Rpg/Entities/Enemy.h"

#include "Rpg/Systems/CombatSystem.h"
#include "Rpg/Systems/StatusModifierSystem.h"
#include "Rpg/Systems/InventorySystem.h"

namespace Rpg::Tests
{

void runCombatTests()
{
  IdFactory idFactory;

  StatusModifier healthUp {
    idFactory.allocate(1000),
    StatusModifierType::Health,
    StackComponent {99, 1},
    10
  };

  StatusModifier healthDown {
    idFactory.allocate(1001),
    StatusModifierType::Health,
    StackComponent {99, 1},
    -10
  };

  StatusModifier strengthUp {
    idFactory.allocate(1002),
    StatusModifierType::Strength,
    StackComponent {99, 1},
    10
  };

  StatusModifier strengthDown {
    idFactory.allocate(1003),
    StatusModifierType::Strength,
    StackComponent {99, 1},
    -10
  };

  StatusModifier defenseUp {
    idFactory.allocate(1004),
    StatusModifierType::Defense,
    StackComponent {99, 1},
    10
  };

  StatusModifier defenseDown {
    idFactory.allocate(1005),
    StatusModifierType::Defense,
    StackComponent {99, 1},
    -10
  };

  const Consumable consumable {
    .id = idFactory.allocate(100),
    .stack = {99, 10},
    .modifier = healthUp,
  };

  const Weapon weapon {
    .id = idFactory.allocate(101),
    .stack = {1, 1},
    .strength = {5, 5},
    .modifier = strengthUp,
  };

  const Armor armor {
    .id = idFactory.allocate(102),
    .stack = {1, 1},
    .defense = {5, 5},
    .modifier = defenseUp,
  };

  Character protagonist {
    .id = idFactory.allocate(1),
    .health = {100, 100, 100},
    .strength = {20, 20},
    .defense = {20, 20},
  };

  Enemy antagonist {
    .id = idFactory.allocate(2),
    .health = {100, 100, 100},
    .strength = {50, 50},
    .defense = {30, 30},
  };

  printEntity(protagonist);
  printEntity(antagonist);

  protagonist.weaponInventory.add(weapon);
  protagonist.armorInventory.add(armor);
  InventorySystem::equipWeapon(weapon, protagonist.equipment, protagonist.weaponInventory);
  InventorySystem::equipArmor(armor, protagonist.equipment, protagonist.armorInventory);
  StatusModifierSystem::addModifier(weapon.modifier, protagonist.modifierList);
  StatusModifierSystem::addModifier(armor.modifier, protagonist.modifierList);
  StatusModifierSystem::updateModifiers(protagonist.modifierList, protagonist.strength);
  StatusModifierSystem::updateModifiers(protagonist.modifierList, protagonist.defense);
  printEntity(protagonist);

  CombatSystem::applyDamage(antagonist, protagonist);
  printEntity(protagonist);

  StatusModifierSystem::addModifier(defenseDown, antagonist.modifierList);
  StatusModifierSystem::updateModifiers(antagonist.modifierList, antagonist.defense);
  CombatSystem::applyDamage(protagonist, antagonist);
  printEntity(antagonist);

  CombatSystem::applyDamage(antagonist, protagonist);
  printEntity(protagonist);

  protagonist.health.heal(100);
  printEntity(protagonist);

  antagonist.health.takeDamage(100);
  printEntity(antagonist);

  InventorySystem::addItem(consumable, protagonist.consumableInventory);
  InventorySystem::useConsumable(consumable, protagonist.consumableInventory);
  StatusModifierSystem::addModifier(consumable.modifier, protagonist.modifierList);
  StatusModifierSystem::updateModifiers(protagonist.modifierList, protagonist.health);
  printEntity(protagonist);

  protagonist.health.reset();
  protagonist.strength.reset();
  protagonist.defense.reset();
  printEntity(protagonist);
}

} // namespace Rpg::Tests

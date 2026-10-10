# Folio

A C++ video game gameplay framework. Currently working on a character experience and turn-based combat system,
as time allows.

## Structure

- `include/Folio`: Public API headers. Function declarations, class definitions, templates, and simple logic.
- `src/`: Implementations and complex logic.
- `tests/`: Tests for existing logic.

## Architecture

The type aliases used throughout the project are declared in `include/Folio/Core/Types.h`. I wondered if it
was perhaps excessive writing out a list of aliases all to `std::int32_t`, but I decided to keep them for their
expressiveness:

```c++
// include/Folio/Components/HealthComponent.h
void heal(Health delta) { ... }

// include/Folio/Components/StrengthComponent.h
static constexpr Strength kMaxStrength {99};
```

The project uses a hybrid inheritance and component-based design for game objects, the former to enable
polymorphism and reduce repetition in the members of some objects, and the latter for flexibility and reusability
across various different objects. All game objects are identified by a type ID and a unique instance ID. Using
inheritance for certain objects has the added benefit of greater intuitiveness at the call site:

```c++
// src/Systems/CombatSystem.cpp
void CombatSystem::applyDamage(IdComponent sourceId, IdComponent targetId) const {
  auto source {m_entityManager.find<Combatant>(sourceId)};
  auto target {m_entityManager.find<Combatant>(targetId)};

  if (!source || !target || !source->health().alive() || !target->health().alive()) return;

  const auto damage {calculateDamage(source->strength(), target->defense())};
  target->takeDamage(damage);

  m_healthChangedManager.dispatch(EHealthChanged {.sourceId = sourceId, .targetId = targetId});
}
```

Additionally, factories create game object instances and systems facilitate the communication between game
objects. The `EntityManager` manages the lifetime of active entities, and the `EventManager` calls multiple systems
whenever an event fires. For instance, equipping a weapon might dispatch an `EApplyStatusModifier` event, which
coordinates the relevant systems to apply the modifier internally, adjust the UI accordingly, or play the appropriate
audio and animation (though currently, only logic for applying the modifier internally has been implemented). Systems
automatically subscribe to event managers upon construction and unsubscribe upon destruction.

### Example Usage

```c++
#include "Folio/Entities/Character.h"
#include "Folio/Systems/EntityManager.h"
#include "Folio/Systems/CombatSystem.h"
...

IdFactory idFactory;
EntityManager entityManager {idFactory, healthChangedManager, ...};
CombatSystem combatSystem {entityManager, damageManager, ...};
ModifierSystem modifierSystem {entityManager, applyStatusModifierManager, ...};
...

auto protagonistId {entityFactory.create(protagonistBlueprint)};
auto antagonistId {entityFactory.create(antagonistBlueprint)};
...

inventorySystem.equipWeapon(weaponId, protagonistId);
modifierSystem.addStatusModifier(defenseDown, protagonistId, antagonistId);
combatSystem.applyDamage(protagonistId, antagonistId);
...
```

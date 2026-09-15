cmake_minimum_required(VERSION 4.2)
project(Rpg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Rpg
        # Components
        include/Rpg/Components/ContainerComponent.h
        include/Rpg/Components/DefenseComponent.h
        include/Rpg/Components/EquipmentComponent.h
        include/Rpg/Components/HealthComponent.h
        include/Rpg/Components/IdComponent.h
        include/Rpg/Components/StackComponent.h
        include/Rpg/Components/StrengthComponent.h

        # Concepts
        include/Rpg/Concepts/AttributeComponent.h
        include/Rpg/Concepts/ContainerItem.h

        # Core
        include/Rpg/Core/Types.h

        # Entities
        include/Rpg/Entities/Character.h
        include/Rpg/Entities/CharacterBlueprint.h
        include/Rpg/Entities/Combatant.h
        include/Rpg/Entities/Enemy.h
        include/Rpg/Entities/EnemyBlueprint.h
        include/Rpg/Entities/Entity.h
        src/Entities/Character.cpp
        src/Entities/Combatant.cpp
        src/Entities/Enemy.cpp

        # Events
        include/Rpg/Events/ApplyDamageEvent.h
        include/Rpg/Events/ApplyInstantModifierEvent.h
        include/Rpg/Events/ApplyStatusModifierEvent.h
        include/Rpg/Events/RemoveStatusModifierEvent.h

        # Factories
        include/Rpg/Factories/EntityFactory.h
        include/Rpg/Factories/IdFactory.h

        # Items
        include/Rpg/Items/Armor.h
        include/Rpg/Items/Consumable.h
        include/Rpg/Items/Weapon.h

        # Modifiers
        include/Rpg/Modifiers/InstantModifier.h
        include/Rpg/Modifiers/InstantModifierType.h
        include/Rpg/Modifiers/StatusModifier.h
        include/Rpg/Modifiers/StatusModifierType.h

        # Systems
        include/Rpg/Systems/CombatSystem.h
        include/Rpg/Systems/EntityManager.h
        include/Rpg/Systems/EventManager.h
        include/Rpg/Systems/InventorySystem.h
        include/Rpg/Systems/ModifierSystem.h
        include/Rpg/Systems/SystemType.h
        include/Rpg/Systems/TurnManager.h
        include/Rpg/Systems/TurnSystem.h
        src/Systems/CombatSystem.cpp
        src/Systems/EntityManager.cpp
        src/Systems/InventorySystem.cpp
        src/Systems/ModifierSystem.cpp
        src/Systems/TurnManager.cpp
        src/Systems/TurnSystem.cpp
)

target_include_directories(Rpg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Rpg)

add_executable(test tests/test.cpp
        tests/Utilities.h
        tests/Utilities.cpp
        tests/CombatTest.cpp
)
target_link_libraries(test PRIVATE Rpg)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

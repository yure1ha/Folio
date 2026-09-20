cmake_minimum_required(VERSION 4.2)
project(Folio)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Folio
        # Components
        include/Folio/Components/ContainerComponent.h
        include/Folio/Components/DefenseComponent.h
        include/Folio/Components/EquipmentComponent.h
        include/Folio/Components/HealthComponent.h
        include/Folio/Components/IdComponent.h
        include/Folio/Components/StackComponent.h
        include/Folio/Components/StrengthComponent.h
        include/Folio/Components/ValueComponent.h

        # Concepts
        include/Folio/Concepts/AttributeComponent.h
        include/Folio/Concepts/ContainerItem.h

        # Core
        include/Folio/Core/Types.h

        # Entities
        include/Folio/Entities/Character.h
        include/Folio/Entities/CharacterBlueprint.h
        include/Folio/Entities/Combatant.h
        include/Folio/Entities/Enemy.h
        include/Folio/Entities/EnemyBlueprint.h
        include/Folio/Entities/Entity.h
        include/Folio/Entities/EntityType.h
        src/Entities/Character.cpp
        src/Entities/Combatant.cpp
        src/Entities/Enemy.cpp

        # Events
        include/Folio/Events/EApplyDamage.h
        include/Folio/Events/EApplyInstantModifier.h
        include/Folio/Events/EApplyStatusModifier.h
        include/Folio/Events/ECharacterDefeated.h
        include/Folio/Events/EEnemyDefeated.h
        include/Folio/Events/EHealthChanged.h
        include/Folio/Events/ERemoveStatusModifier.h

        # Factories
        include/Folio/Factories/EntityFactory.h
        include/Folio/Factories/IdFactory.h

        # Items
        include/Folio/Items/Armor.h
        include/Folio/Items/Consumable.h
        include/Folio/Items/Weapon.h

        # Modifiers
        include/Folio/Modifiers/InstantModifier.h
        include/Folio/Modifiers/InstantModifierType.h
        include/Folio/Modifiers/StatusModifier.h
        include/Folio/Modifiers/StatusModifierType.h

        # Systems
        include/Folio/Systems/CombatSystem.h
        include/Folio/Systems/EntityManager.h
        include/Folio/Systems/EventManager.h
        include/Folio/Systems/InventorySystem.h
        include/Folio/Systems/ModifierSystem.h
        include/Folio/Systems/SystemType.h
        include/Folio/Systems/TurnManager.h
        include/Folio/Systems/TurnSystem.h
        src/Systems/CombatSystem.cpp
        src/Systems/EntityManager.cpp
        src/Systems/InventorySystem.cpp
        src/Systems/ModifierSystem.cpp
        src/Systems/TurnManager.cpp
        src/Systems/TurnSystem.cpp
)

target_include_directories(Folio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Folio)

add_executable(test tests/test.cpp
        tests/Utilities.h
        tests/Utilities.cpp
        tests/CombatTest.cpp
)
target_link_libraries(test PRIVATE Folio)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

cmake_minimum_required(VERSION 4.2)
project(Rpg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Rpg
        # Components
        include/Rpg/Components/IdComponent.h
        include/Rpg/Components/ContainerComponent.h
        include/Rpg/Components/HealthComponent.h
        include/Rpg/Components/DefenseComponent.h
        include/Rpg/Components/StrengthComponent.h
        include/Rpg/Components/StackComponent.h
        include/Rpg/Components/EquipmentComponent.h

        # Concepts
        include/Rpg/Concepts/AttributeComponent.h
        include/Rpg/Concepts/ContainerItem.h

        # Entities
        include/Rpg/Entities/EntityManager.h
        include/Rpg/Entities/Entity.h
        include/Rpg/Entities/Combatant.h
        src/Entities/Combatant.cpp
        include/Rpg/Entities/Character.h
        src/Entities/Character.cpp
        include/Rpg/Entities/Enemy.h
        src/Entities/Enemy.cpp
        include/Rpg/Entities/CharacterBlueprint.h
        include/Rpg/Entities/EnemyBlueprint.h

        # Events
        include/Rpg/Events/EventManager.h
        include/Rpg/Events/ApplyStatusModifierEvent.h
        include/Rpg/Events/ApplyDamageEvent.h
        include/Rpg/Events/UseItemEvent.h

        # Factories
        include/Rpg/Factories/IdFactory.h

        # Items
        include/Rpg/Items/Consumable.h
        include/Rpg/Items/Weapon.h
        include/Rpg/Items/Armor.h

        # Modifiers
        include/Rpg/Modifiers/StatusModifierType.h
        include/Rpg/Modifiers/StatusModifier.h

        # Systems
        include/Rpg/Systems/SystemType.h
        include/Rpg/Systems/StatusModifierSystem.h
        src/Systems/StatusModifierSystem.cpp
        include/Rpg/Systems/InventorySystem.h
        src/Systems/InventorySystem.cpp
        include/Rpg/Systems/CombatSystem.h
        src/Systems/CombatSystem.cpp
)

target_include_directories(Rpg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Rpg)

add_executable(test tests/test.cpp
        tests/CombatTest.cpp
        tests/Helpers.h
)
target_link_libraries(test PRIVATE Rpg)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

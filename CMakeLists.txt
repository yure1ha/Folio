cmake_minimum_required(VERSION 4.2)
project(Rpg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Rpg
        # Data
        include/Rpg/Data/Entities/CharacterBlueprint.h
        include/Rpg/Data/Entities/EnemyBlueprint.h
        include/Rpg/Data/Items/ConsumableBlueprint.h
        include/Rpg/Data/Items/WeaponBlueprint.h
        include/Rpg/Data/Items/ArmorBlueprint.h
        include/Rpg/Data/StatusModifierType.h
        include/Rpg/Data/SystemType.h

        # Concepts
        include/Rpg/Concepts/AttributeComponent.h
        include/Rpg/Concepts/ContainerItem.h

        # Components
        include/Rpg/Components/IdComponent.h
        include/Rpg/Components/StatusModifierComponent.h
        include/Rpg/Components/Attributes/HealthComponent.h
        include/Rpg/Components/Attributes/DefenseComponent.h
        include/Rpg/Components/Attributes/StrengthComponent.h
        include/Rpg/Components/StackComponent.h
        include/Rpg/Components/Containers/ContainerComponent.h
        include/Rpg/Components/Containers/EquipmentComponent.h

        # Entities
        include/Rpg/Entities/Character.h
        include/Rpg/Entities/Enemy.h
        src/Entities/Character.cpp

        # Items
        include/Rpg/Items/Consumable.h
        include/Rpg/Items/Weapon.h
        include/Rpg/Items/Armor.h

        # Events
        include/Rpg/Events/ApplyStatusModifierEvent.h
        include/Rpg/Events/ApplyDamageEvent.h
        include/Rpg/Events/EventManager.h

        # Factories
        include/Rpg/Factories/IdFactory.h
        include/Rpg/Factories/EntityFactory.h
        include/Rpg/Factories/ItemFactory.h

        # Systems
        include/Rpg/Systems/StatusModifierSystem.h
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

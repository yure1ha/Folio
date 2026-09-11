#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/StackComponent.h"
#include "Rpg/Modifiers/StatusModifier.h"

#include <cstdint>

namespace Rpg {

struct Consumable {
    IdComponent id;
    StackComponent stack;
    StatusModifier modifier;

    std::int32_t sortKey() const { return stack.current(); }
};

} // namespace Rpg

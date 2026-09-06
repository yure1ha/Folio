#pragma once

#include "Rpg/Components/IdComponent.h"

namespace Rpg
{

struct ApplyStatusModifierEvent
{
  IdComponent modifierId;
  IdComponent targetId;
};

} // namespace Rpg

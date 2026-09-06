#pragma once

#include "Rpg/Components/IdComponent.h"

namespace Rpg
{

struct ApplyDamageEvent
{
  IdComponent attackerId;
  IdComponent targetId;
};

} // namespace Rpg

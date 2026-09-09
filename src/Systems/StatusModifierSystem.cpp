#include "Rpg/Systems/StatusModifierSystem.h"

namespace Rpg::StatusModifierSystem
{

void addModifier(const StatusModifier& modifier,
                 StatusModifierList& modifierList)
{
  modifierList.add(modifier);
}

void removeModifier(const StatusModifier& modifier,
                    StatusModifierList& modifierList)
{
  modifierList.remove(modifier.id);
}

} // namespace Rpg::StatusModifierSystem

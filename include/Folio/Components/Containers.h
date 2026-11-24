#pragma once

#include "Folio/Components/ContainerComponent.h"
#include "Folio/Items/Armor.h"
#include "Folio/Items/Consumable.h"
#include "Folio/Items/Weapon.h"
#include "Folio/Modifiers/StatusModifier.h"

namespace Folio {

using StatusModifierList = ContainerComponent<StatusModifier>;
using WeaponInventory = ContainerComponent<Weapon>;
using ArmorInventory = ContainerComponent<Armor>;
using ConsumableInventory = ContainerComponent<Consumable>;

} // namespace Folio

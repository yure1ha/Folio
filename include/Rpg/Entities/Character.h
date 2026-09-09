#pragma once

#include "Rpg/Entities/Entity.h"
#include "Rpg/Entities/CharacterBlueprint.h"

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Components/HealthComponent.h"
#include "Rpg/Components/StrengthComponent.h"
#include "Rpg/Components/DefenseComponent.h"
#include "Rpg/Components/EquipmentComponent.h"
#include "Rpg/Components/ContainerComponent.h"

#include "Rpg/Items/Consumable.h"
#include "Rpg/Items/Weapon.h"
#include "Rpg/Items/Armor.h"
#include "Rpg/Modifiers/StatusModifier.h"

namespace Rpg
{

class Character : public Entity
{
public:
  Character(IdComponent id, const CharacterBlueprint& bp);

  using ConsumableInventory = ContainerComponent<Consumable>;
  using WeaponInventory     = ContainerComponent<Weapon>;
  using ArmorInventory      = ContainerComponent<Armor>;
  using ModifierList        = ContainerComponent<StatusModifier>;

  HealthComponent& health()       { return m_health; }
  StrengthComponent& strength()   { return m_strength; }
  DefenseComponent& defense()     { return m_defense; }
  EquipmentComponent& equipment() { return m_equipment; }

  ConsumableInventory& consumables() { return m_consumables; }
  WeaponInventory& weapons()         { return m_weapons; }
  ArmorInventory& armor()            { return m_armor; }
  ModifierList& modifiers()          { return m_modifiers; }

  const HealthComponent& health() const       { return m_health; }
  const StrengthComponent& strength() const   { return m_strength; }
  const DefenseComponent& defense() const     { return m_defense; }
  const EquipmentComponent& equipment() const { return m_equipment; }

  const ConsumableInventory& consumables() const { return m_consumables; }
  const WeaponInventory& weapons() const         { return m_weapons; }
  const ArmorInventory& armor() const            { return m_armor; }
  const ModifierList& modifiers() const          { return m_modifiers; }

private:
  HealthComponent    m_health;
  StrengthComponent  m_strength;
  DefenseComponent   m_defense;
  EquipmentComponent m_equipment;

  ConsumableInventory m_consumables;
  WeaponInventory     m_weapons;
  ArmorInventory      m_armor;
  ModifierList        m_modifiers;
};

} // namespace Rpg

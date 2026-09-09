#pragma once

#include "Rpg/Components/IdComponent.h"
#include "Rpg/Concepts/ContainerItem.h"

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

namespace Rpg
{

template <Concepts::ContainerItem T>
class ContainerComponent
{
public:
  ContainerComponent() = default;

  explicit ContainerComponent(std::vector<T> items)
      : m_items {std::move(items)}
  {
  }

  const std::vector<T>& items() const { return m_items; }

  auto begin() { return m_items.begin(); }
  auto end()   { return m_items.end(); }

  auto begin() const { return m_items.begin(); }
  auto end() const   { return m_items.end(); }

  bool contains(IdComponent id) const
  {
    return std::ranges::any_of(m_items, [id](const T& comp)
    {
      return id == comp.id;
    });
  }

  auto find(IdComponent id)
  {
    return std::ranges::find_if(m_items, [id](const T& comp)
    {
      return id == comp.id;
    });
  }

  auto find(IdComponent id) const
  {
    return std::ranges::find_if(m_items, [id](const T& comp)
    {
      return id == comp.id;
    });
  }

  void add(T item, std::int32_t amount = 1)
  {
    if (auto it {find(item.id)}; it != end())
    {
      it->stack.increase(amount);
      return;
    }

    m_items.push_back(std::move(item));
  }

  void remove(IdComponent id, std::int32_t amount = 1)
  {
    auto it {find(id)};
    if (it == end()) return;

    it->stack.decrease(amount);
    if (it->stack.empty())
    {
      std::erase_if(m_items, [id](const T& comp)
      {
        return id == comp.id;
      });
    }
  }

  void sort()
  {
    std::ranges::sort(m_items, [](const T& a, const T& b)
    {
      if (a.sortKey() != b.sortKey())
      {
        return a.sortKey() > b.sortKey();
      }

      return a.id > b.id;
    });
  }

private:
  std::vector<T> m_items {};
};

} // namespace Rpg

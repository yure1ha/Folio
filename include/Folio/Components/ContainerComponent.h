#pragma once

#include "Folio/Components/IdComponent.h"
#include "Folio/Concepts/ContainerItem.h"
#include "Folio/Core/Types.h"

#include <algorithm>
#include <utility>
#include <vector>

namespace Folio {

template <Concepts::ContainerItem T>
class ContainerComponent {
public:
  using Iterator = std::vector<T>::iterator;
  using ConstIterator = std::vector<T>::const_iterator;

  ContainerComponent() = default;

  explicit ContainerComponent(std::vector<T> items) : m_items {std::move(items)} {}

  const std::vector<T>& items() const { return m_items; }

  auto begin() { return m_items.begin(); }

  auto end() { return m_items.end(); }

  auto begin() const { return m_items.begin(); }

  auto end() const { return m_items.end(); }

  bool contains(IdComponent id) const { return find(id) != end(); }

  ConstIterator find(IdComponent id) const {
    return std::ranges::find_if(m_items, [id](const T& comp) {
      return id == comp.id;
    });
  }

  Iterator find(IdComponent id) {
    return std::ranges::find_if(m_items, [id](const T& comp) {
      return id == comp.id;
    });
  }

  void add(T item, Stack delta = 1) {
    if (auto it {find(item.id)}; it != end()) {
      it->stack.increase(delta);
      return;
    }

    m_items.push_back(std::move(item));
  }

  void remove(IdComponent id, Stack delta = 1) { remove(find(id), delta); }

  void remove(Iterator it, Stack delta = 1) {
    if (it == end()) return;

    it->stack.decrease(delta);
    if (it->stack.empty()) {
      m_items.erase(it);
    }
  }

  void sort() {
    std::ranges::sort(m_items, [](const T& a, const T& b) {
      if (a.sortKey() != b.sortKey()) {
        return a.sortKey() > b.sortKey();
      }

      return a.id > b.id;
    });
  }

private:
  std::vector<T> m_items {};
};

} // namespace Folio

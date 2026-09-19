#pragma once

#include <concepts>

namespace Folio::Concepts {

template <typename T>
concept ContainerItem = requires(const T& item) {
  { item.sortKey() } -> std::totally_ordered;
};

} // namespace Folio::Concepts

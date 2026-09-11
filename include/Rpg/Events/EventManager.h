#pragma once

#include "Rpg/Systems/SystemType.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

namespace Rpg {

template <typename T>
class EventManager {
  public:
    using SystemCallback = std::function<void(const T&)>;

    struct Subscriber {
        SystemType type {};
        SystemCallback callback {};
    };

    void subscribe(SystemType systemType, SystemCallback callback) {
        m_subscribers.push_back(Subscriber {.type = systemType, .callback = std::move(callback)});
    }

    void unsubscribe(SystemType systemType) {
        std::erase_if(m_subscribers, [systemType](const Subscriber& subscriber) {
            return systemType == subscriber.type;
        });
    }

    void dispatch(const T& event) const {
        for (const auto& subscriber : m_subscribers) {
            subscriber.callback(event);
        }
    }

  private:
    std::vector<Subscriber> m_subscribers {};
};

} // namespace Rpg

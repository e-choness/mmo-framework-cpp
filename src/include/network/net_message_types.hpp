#pragma once
#include "std_common.hpp"

namespace network{
    enum class MessageType : uint32_t {
        Accept,
        Deny,
        Ping,
        All,
        Message
    };
}

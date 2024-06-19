#pragma once
#include "std_common.hpp"

namespace client{
    enum class MessageType : uint32_t {
        Accept,
        Deny,
        Ping,
        All,
        Message
    };
}

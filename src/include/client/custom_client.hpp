#pragma once
#include "net_client.hpp"
#include "net_message_types.hpp"

namespace client{
    class CustomClient : public network::ClientInterface<network::MessageType>{
    public:
        CustomClient();

        ~CustomClient() override= default;
    };
}



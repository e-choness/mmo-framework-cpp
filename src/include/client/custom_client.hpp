#pragma once
#include "net_client.hpp"
#include "client_types.hpp"

namespace client{
    class CustomClient : public network::ClientInterface<MessageType>{
    public:
        CustomClient();

        ~CustomClient() override= default;
    };
}



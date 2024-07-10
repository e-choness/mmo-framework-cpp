#pragma once
#include "net_client.hpp"
#include "net_message_types.hpp"

namespace client{
    class CustomClient : public network::ClientInterface<network::MessageType>{
    public:
        CustomClient() {
            {std::cout << "[Client] Started.\n"; }
        }
        ~CustomClient() override= default;
        void ping(){
            network::Message<network::MessageType> message;
            message.mHeader.mId = network::MessageType::Ping;

            TimePoint timeNow = getNow();
            message << timeNow;

            send(message);
        }
    };
}



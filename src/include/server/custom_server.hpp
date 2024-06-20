#pragma once
#include "net_message_types.hpp"
#include "net_server.hpp"


namespace server{
    class CustomServer : public network::ServerInterface<network::MessageType>{
        public:
        [[maybe_unused]] explicit CustomServer(uint16_t port) : network::ServerInterface<network::MessageType>(port){

            }
        protected:
            bool onClientConnect(std::shared_ptr<network::Connection<network::MessageType>> client) override{
                return true;
            }

            void onClientDisconnect(std::shared_ptr<network::Connection<network::MessageType>> client) override{

            }

            void onMessage(std::shared_ptr<network::Connection<network::MessageType>> client, const network::Message<network::MessageType>& message) override{

            }
    };
}

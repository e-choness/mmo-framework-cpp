#pragma once
#include "server_types.hpp"
#include "net_server.hpp"


namespace server{
    class CustomServer : public network::ServerInterface<MessageType>{
        public:
        [[maybe_unused]] explicit CustomServer(uint16_t port) : network::ServerInterface<MessageType>(port){

            }
        protected:
            bool onClientConnect(std::shared_ptr<network::Connection<MessageType>> client) override{
                return true;
            }

            void onClientDisconnect(std::shared_ptr<network::Connection<MessageType>> client) override{

            }

            void onMessage(std::shared_ptr<network::Connection<MessageType>> client, const network::Message<MessageType>& message) override{

            }
    };
}

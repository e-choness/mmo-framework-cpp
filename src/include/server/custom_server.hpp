#pragma once
#include "net_message_types.hpp"
#include "net_server.hpp"


namespace server{
    class CustomServer : public network::ServerInterface<network::MessageType>{
        public:
        [[maybe_unused]] explicit CustomServer(uint16_t port) : network::ServerInterface<network::MessageType>(port){

            }
        protected:
            // Gets called when a client connect to the server
            bool onClientConnect(std::shared_ptr<network::Connection<network::MessageType>> client) override{
                return true;
            }

            // Gets called when a client disconnect from the server
            void onClientDisconnect(std::shared_ptr<network::Connection<network::MessageType>> client) override{

            }

            // Gets called when a message arrives
            void onMessage(std::shared_ptr<network::Connection<network::MessageType>> client, const network::Message<network::MessageType>& message) override{
                switch (message.mHeader.mId) {
                    case network::MessageType::Ping:{
                        std::cout << "[Client " << client.get() << "]: pings the server.\n";
                        client->send(message);
                    }
                    break;

                }
            }
    };
}

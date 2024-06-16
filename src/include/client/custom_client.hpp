#pragma once
#include "net_client.hpp"
#include "client_types.hpp"

namespace client{
class CustomClient : public network::ClientInterface<CustomMessageType>{
    public:
//        CustomClient();
//        void run();
        ~CustomClient() override;

        bool FireBullet(float x, float y){
            network::Message<CustomMessageType> message;
            message.mHeader.mId = CustomMessageType::Fire;
            message << x << y;
            mConnection->send(message);
        }
//    private:
//        void grabAsync(TcpSocket& socket);
//        std::vector<char> mBuffer;
    };
}



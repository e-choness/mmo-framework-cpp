#include "chat_server.hpp"
#include "net_message.hpp"

enum class CustomMessageType : uint32_t {
    Fire,
    Move
};

void server::ChatServer::run() {
    network::Message<CustomMessageType> message;
    message.mHeader.mId = CustomMessageType::Fire;

    int a = 1;
    bool b = true;
    float c = 3.1415926f;

    struct{
        float x;
        float y;
    } d[5];

    message << a << b << c << d;

    a = 99;
    b = false;
    c = 99.0f;

    message >> d >> c >> b >> a;

}



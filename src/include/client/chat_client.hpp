#pragma once
#include "../common/std_common.hpp"
#include "asio_definitions.hpp"

namespace client{
    class ChatClient{
    public:
        ChatClient();
        void run();
    private:
        void grabAsync(TcpSocket& socket);
        std::vector<char> mBuffer;
    };
}

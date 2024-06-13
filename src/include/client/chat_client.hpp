#pragma once
#include <vector>
#include <asio_definitions.hpp>

class ChatClient{
public:
    ChatClient();
    void run();
private:
    void grabAsync(TcpSocket& socket);
    std::vector<char> mBuffer;
};
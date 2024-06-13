#include "chat_server.hpp"

#include <iostream>
#include <boost/asio.hpp>

ChatServer::ChatServer(io_context &io_context, short port) {

}

class ChatServer::Impl{
public:
    Impl(io_context& io_context, short port) : acceptor_(&io_context, tcp::endpoint(tcp::v4(), port)){
        start_accept();
    }

    void start_accept(){

    }
private:
    tcp::acceptor acceptor_;
};

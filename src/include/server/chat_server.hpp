#pragma once
#include <string>
#include <memory>

// Forward declare boost system error_code
namespace boost::asio{
    namespace io_context{
        class io_context;
    }
    namespace ip{
        class tcp;
    }
}

using boost::asio::ip::tcp;
using boost::asio::io_context::io_context;

class ChatServer{
public:
    ChatServer(io_context& io_context, short port)
    void start_accept();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
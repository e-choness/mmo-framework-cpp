#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>


typedef boost::asio::io_context IoContext;
typedef boost::asio::ip::tcp::endpoint TcpEndpoint;
typedef boost::system::error_code ErrorCode;
typedef boost::asio::ip::tcp Tcp;
typedef boost::asio::ip::tcp::resolver TcpResolver;
typedef boost::asio::ip::tcp::socket TcpSocket;
typedef boost::asio::io_context::work ContextWork;
typedef boost::asio::ip::tcp::acceptor TcpAcceptor;

inline boost::asio::ip::address make_address(const std::string& str, ErrorCode ec){
    return boost::asio::ip::make_address(str, ec);
}

template <typename T>
inline auto makeBuffer(std::vector<T>& container){
    return boost::asio::buffer(container.data(), container.size() * sizeof(T));
}

inline auto makeBuffer(std::string& request){
    return boost::asio::buffer(request.data(), request.size());
}

inline auto makeTcpV4(){
    return boost::asio::ip::tcp::v4();
}
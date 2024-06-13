#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>


typedef boost::asio::io_context IoContext;
typedef boost::asio::ip::tcp::endpoint TcpEndpoint;
typedef boost::system::error_code ErrorCode;
typedef boost::asio::ip::tcp Tcp;
typedef boost::asio::ip::tcp::socket TcpSocket;

inline boost::asio::ip::address make_address(const std::string& str, ErrorCode ec){
    return boost::asio::ip::make_address(str, ec);
}
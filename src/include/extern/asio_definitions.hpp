#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>


typedef boost::asio::io_context IoContext;
typedef boost::asio::ip::tcp::endpoint TcpEndpoint;
typedef boost::system::error_code ErrorCode;
typedef boost::asio::ip::tcp::resolver TcpResolver;
typedef boost::asio::ip::tcp::socket TcpSocket;
typedef boost::asio::ip::tcp::acceptor TcpAcceptor;
typedef boost::asio::ip::tcp::resolver::results_type ResultType;

inline auto makeTcpV4(){
    return boost::asio::ip::tcp::v4();
}
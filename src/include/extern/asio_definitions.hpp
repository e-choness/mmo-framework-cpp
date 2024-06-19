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
typedef boost::asio::ip::tcp::resolver::results_type ResultType;

inline boost::asio::ip::address make_address(const std::string& str, ErrorCode ec){
    return boost::asio::ip::make_address(str, ec);
}

template <typename T>
inline auto makeBufferContainer(std::vector<T>& container){
    return boost::asio::buffer(container.data(), container.size() * sizeof(T));
}

inline auto makeBuffer(std::string& request){
    return boost::asio::buffer(request.data(), request.size());
}

template<typename T>
inline auto makeBuffer(T customClass){
    return boost::asio::buffer(customClass, sizeof(T));
}

inline auto makeTcpV4(){
    return boost::asio::ip::tcp::v4();
}

template<typename T, typename Handler>
inline auto asyncReadContainer(TcpSocket socket, std::vector<T>& container, Handler handler){
    return boost::asio::async_read(socket, makeBufferContainer(container), handler);
}

template<typename T, typename Handler>
inline auto asyncRead(TcpSocket socket, T& content, Handler handler){
    return boost::asio::async_read(socket, makeBuffer(content), handler);
}

template<typename T, typename Handler>
inline auto asyncWriteContainer(TcpSocket socket, std::vector<T>& container, Handler handler){
    return boost::asio::async_write(socket, makeBufferContainer(container), handler);
}

template<typename T, typename Handler>
inline auto asyncWrite(TcpSocket socket, T& content, Handler handler){
    return boost::asio::async_write(socket, makeBuffer(content), handler);
}

template<typename Handler>
inline auto post(IoContext& context, Handler handler){
    return boost::asio::post(context, handler);
}

template<typename Handler>
inline auto connectAsync(TcpSocket socket, ResultType& endpoints, Handler handler){
    return boost::asio::async_connect(socket, endpoints, handler);
}
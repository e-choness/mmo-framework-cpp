#include "hello.hpp"
#include <iostream>
#include <boost/asio.hpp>

int handleErrorCode(boost::system::error_code &ec, const std::string& custom_message){
    if(ec.value() != 0){
        // Failed to open the socket
        std::cout
                << custom_message
                << " Error code: "
                << ec.value()
                << " Message: "
                << ec.message();
        return ec.value();
    }
    return 0;
}

void handleSystemErrorCode(boost::system::system_error &error, const std::string& custom_message){
        // Failed to open the socket
        std::cout
                << custom_message
                << " Error code: "
                << error.code()
                << " Message: "
                << error.what();
}

int runEndpointWithFixedIP(){
    // Step1
    // Assume that the client application has already obtained the IP
    // address and the protocol port number.
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    // Used to store information about error that happens while parsing the raw IP-address
    boost::system::error_code ec;

    // Step 2
    // Using IP protocol version independent address representation
    boost::asio::ip::address ip_address =
            boost::asio::ip::address::from_string(raw_ip_address, ec);

    std::string message = "Failed to parse the IP address!";

    auto result = handleErrorCode(ec, message);
    if(result != 0){
        return result;
    }

    // Step 3.
    boost::asio::ip::tcp::endpoint ep(ip_address, port_num);

    // Step 4
    // The endpoint is ready and can be used to specify a particular server
    // in the network the client wants to communicate with.
    std::cout << "This endpoint "<< ip_address.to_string() <<" is ready to communicate.\n";

    return 0;
}

int runEndpointWithGroupIP(){
    // Step 1.
    // Here we assume that the server application has already obtained the protocol port number.
    unsigned short port_num = 3333;

    // Step 2.
    // Create special object of asio::ip::address class
    // It specifies all IP-address available on the host.
    // Note that here we assume that server works over IPv6 protocol.
    boost::asio::ip::address ip_address = boost::asio::ip::address_v6::any();

    // Step 3
    // Open endpoint
    boost::asio::ip::tcp::endpoint ep(ip_address, port_num);

    // Step 4
    // The endpoint is created and can be used to specify the IP addresses and a port number
    // On which the server application wants to listen for incoming connections.
    std::cout << "The endpoint " << ip_address.to_string() << " is ready to communicate.\n";

    return 0;
}

int runSenderOnIPv4(){
    // Step 1
    // An instance of "io_service" class is required by socket constructor
    // all socket class constructors require an object of asio::io_service as an argument
    boost::asio::io_service  ios;

    // Step 2
    // Creating an object of 'tcp' class representing a TCP protocol with IPv4 as underlying protocol
    // It acts like a data structure that contains a set of values that describe the protocol
    boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v4();

//    // Step 3
//    // Instantiating an active TCP socket object
//    boost::asio::ip::tcp::socket sock(ios);
//
//    // Used to store information about error that happens
//    // while opening the socket
//    boost::system::error_code ec;
//
//    // Step 4
//    // Opening the socket
//    sock.open(protocol, ec);
//
//    std::string message = "Failed to open the socket!";
//    // Handle any potential error codes
//    auto result = handleErrorCode(ec, message);
//
//    if(result!=0){
//        return result;
//    }
    try{
        // Step 3+4 from previous example
        boost::asio::ip::tcp::socket sock(ios, protocol);
    }catch(boost::system::system_error& e){
        std::string message = "Failed to open the socket!";
        handleSystemErrorCode(e, message);
    }

    std::cout << "The sender over TCP and IPv4 is open and ready to send data...\n";

    return 0;

}

int runSenderOnIPv6() {
    // Step 1
    // An instance of 'io_device' class is required by socket constructor.
    boost::asio::io_service ios;

    // Step 2
    // Creating an object of 'udp' class representing a UDP protocol with IPv6 as underlying protocol
    boost::asio::ip::udp protocol = boost::asio::ip::udp::v6();

    // Step 3
    // Instantiating an active UDP socket object
    boost::asio::ip::udp::socket sock(ios);

    // Used to store information about error that happens while opening the socekt
    boost::system::error_code ec;

    // Step 4
    // Opening the socket
    sock.open(protocol, ec);

    auto result = handleErrorCode(ec, "Failed to open the socket!");
    if(result != 0){
        return result;
    }

    std::cout << "The sender over UDP and IPv6 is open and ready to send data...\n";

    return 0;
}

int runAcceptorOnIPv6() {
    // Step 1
    // An instance of 'io_service' class is required by socket constructor
    boost::asio::io_service ios;

    // Step 2
    // Creating an object of 'tcp' class representing a TCP protocol with IPv6 as underlying protocol.
    boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v6();

    // Step 3
    // Instantiating an acceptor socket object.
    boost::asio::ip::tcp::acceptor acceptor(ios);

    // Used to store information about error that happens while opening the acceptor socket.
    boost::system::error_code ec;

    // Open an acceptor socket
    acceptor.open(protocol, ec);

    auto result = handleErrorCode(ec, "Failed to open the acceptor socket!");
    if(result !=0){
        return result;
    }

    std::cout << "The acceptor over TCP and IPv6 is open and listening...\n";

    return 0;
}

int runDnsResolver() {
    // Step 1 Assume that the client application has already
    // obtained the DNS name and protocol port number and represented them as strings
    std::string host = "samplehost.com";
    std::string port_num = "3333";

    // Step 2
    // Instantiate a io service
    boost::asio::io_service ios;

    // Step 3
    // Creating a query
    boost::asio::ip::tcp::resolver::query resolver_query(
            host,
            port_num,
            boost::asio::ip::tcp::resolver::query::numeric_service);

    // Step 4 Creating a resolver
    boost::asio::ip::tcp::resolver resolver(ios);

    // Used to store information about error that happens during the resolution process
    boost::system::error_code ec;

    // Step 5
    boost::asio::ip::tcp::resolver::iterator it =
            resolver.resolve(resolver_query, ec);

    auto result = handleErrorCode(ec, "Failed to resolve a DNS name!");
    if(result != 0){
        return result;
    }

    std::cout << "The DNS resolver successfully translated domain name to ip...\n";

    return 0;
}


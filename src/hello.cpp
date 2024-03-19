#include <iostream>
#include "hello.hpp"

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

int runIOServiceOnIPv4(){
    // Step 1
    // An instance of "io_service" class is required by socket constructor
    boost::asio::io_service  ios;

    // Step 2
    // Creating an object of 'tcp' class representing a TCP protocol with IPv4 as underlying protocol
    boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v4();

    // Step 3
    // Instantiating an active TCP socket object
    boost::asio::ip::tcp::socket sock(ios);

    // Used to store information about error that happens
    // while opening the socket
    boost::system::error_code ec;

    // Step 4
    // Opening the socket
    sock.open(protocol, ec);

    std::string message = "Failed to open the socket!";
    // Handle any potential error codes
    auto result = handleErrorCode(ec, message);

    if(result!=0){
        return result;
    }

    std::cout << "The socket is open and listening...\n";

    return 0;

}


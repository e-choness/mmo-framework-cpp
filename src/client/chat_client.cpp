#include <asio_definitions.hpp>
#include <iostream>
#include "chat_client.hpp"


void ChatClient::run() {
    ErrorCode errorCode;

    // Create a context where the platform specific interface
    IoContext context;

    // Grab an endpoint for this one to connect to
    TcpEndpoint endpoint(make_address("93.184.216.34", errorCode), 80);

    // Create a socket and add context to run the underlying implementation
    TcpSocket socket(context);

    errorCode = socket.connect(endpoint, errorCode);

    std::string feedback;
    feedback = ( !errorCode) ? "Connected!\n" : "Failed to connect to address.\n" + errorCode.message();
    std::cout << feedback;
}


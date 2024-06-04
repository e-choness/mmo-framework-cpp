#pragma once
#include <string>

// Forward declare boost system error_code
namespace boost::system{
    class error_code;
    class system_error;
}

// Error handling
int handleErrorCode(boost::system::error_code &ec, const std::string& custom_message);
void handleSystemErrorCode(boost::system::system_error &error, const std::string& custom_message);

// Endpoint functions
int runEndpointWithFixedIP();
int runEndpointWithGroupIP();

// sender functions
int runSenderOnIPv4();
int runSenderOnIPv6();

// acceptor functions
int runAcceptorOnIPv6();

// DNS resolver
int runDnsResolver();
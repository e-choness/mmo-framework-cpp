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

// Socket functions
int runIOServiceOnIPv4();
int runIOServiceOnIPv6();


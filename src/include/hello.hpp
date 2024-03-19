//#pragma once
#include <boost/asio.hpp>
#include <string>

int handleErrorCode(boost::system::error_code &ec, const std::string& custom_message);
int runEndpointWithFixedIP();
int runEndpointWithGroupIP();
int runIOServiceOnIPv4();


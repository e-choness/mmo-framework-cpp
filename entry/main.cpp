#include "hello.hpp"

int main(int argc, char *argv[]){

//    auto result = runEndpointWithFixedIP();
//    auto result = runEndpointWithGroupIP();
//    auto result = runIOServiceOnIPv4();
    auto result = runIOServiceOnIPv6();

    return result == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
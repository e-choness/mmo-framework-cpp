#include <iostream>
#include "hello.hpp"

int main(int argc, char *argv[]){

    auto result = runEndpoint();

    return result == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
#include "custom_client.hpp"

int main(int argc, char **argv){
    client::CustomClient client;
    client.connect("127.0.0.1", 60000);
    return 0;
}

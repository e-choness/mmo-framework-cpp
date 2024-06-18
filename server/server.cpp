#include "custom_server.hpp"

int main(int argc, char **argv){

   server::CustomServer server(60000);
   server.start();

   while(true){
       server.update();
   }

   return 0;
}
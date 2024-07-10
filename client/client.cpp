#include "custom_client.hpp"

bool key[3] = { false, false, false };
bool old_key[3] = { false, false, false };

void updateOldKeys(){
    for(int i=0; i<3; i++)
        old_key[i] = key[i];
}

int main(int argc, char **argv){
    client::CustomClient client;
    client.connect("127.0.0.1", 60000);

    bool isQuit = false;
    while(!isQuit){

        key[0] = (GetAsyncKeyState('1') & 0x8000) != 0;
        key[1] = (GetAsyncKeyState('2') & 0x8000) != 0;
        key[2] = (GetAsyncKeyState('3') & 0x8000) != 0;

        if(key[1] && !old_key[1]) {
            client.ping();
            std::cout << "[Client] pressed 2.\n";
        }
        if(key[2] && !old_key[2]) {
            isQuit = true;
            std::cout << "[Client] pressed 3.\n";
        }

        updateOldKeys();

        if(client.isConnected()){
            if(!client.incoming().isEmpty()){
                network::Message<network::MessageType> message = client.incoming().popFront().mMessage;

                switch (message.mHeader.mId) {
                    case network::MessageType::Ping:
                    {
                        TimePoint timeNow = getNow();
                        TimePoint timeThen;

                        message >> timeThen;
                        std::cout << "[Client] Ping:" << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
                    }
                        break;
                }
            }
        }else{
            std::cout << "The server is down.\n";
            isQuit = true;
        }
    }

    return 0;
}

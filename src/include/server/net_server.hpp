#pragma once
#include "net_ts_queue.hpp"
#include "net_message.hpp"
#include "net_connection.hpp"

namespace network{
    template<typename T>
    class ServerInterface{
    public:
        ServerInterface(uint16_t port) : mAcceptor(mContext, TcpEndpoint(makeTcpV4(), port)){

        }

        virtual ~ServerInterface(){
            stop();
        }

        bool start(){
            try{
                // Waiting for incoming messages from the client
                waitForClientAsync();

                // Make sure the context thread is busy and always open to listening to connection.
                mContextThread = std::thread([this](){ mContext.run(); });
            }catch (std::exception& e){
                std::cerr << "[Server] Exception: " << e.what() << "\n";
                return false;
            }

            std::cout << "[Server] Started.\n";
            return true;
        }

        void stop(){
            // Ask to close the io context
            mContext.stop();

            // Join the context thread after it closes
            if(mContextThread.joinable()) mContextThread.join();

            // Output stop logs
            std::cout << "[Server] Stopped.\n";
        }

        // Wait for client connection - async function
        void waitForClientAsync(){
            mAcceptor.async_accept([this](){});
        }

        void messageClient(std::shared_ptr<Connection<T>> client, const Message<T>& message){

        }

        void messageAllClients(const Message<T>& message, std::shared_ptr<Connection<T>> ignoreClient = nullptr){

        }

    protected:
        virtual bool onClientConnect(std::shared_ptr<Connection<T>> client){
            return false;
        }

        virtual bool onClientDisconnect(std::shared_ptr<Connection<T>> client){
            return false;
        }

        virtual void onMessage(std::shared_ptr<Connection<T>> client, const Message<T> message){

        }
    protected:
        // Thread safe queue for incoming messages
        TSQueue<OwnedMessage<T>> mMessagesIn;

        // IO context for asio acceptor and socket
        IoContext  mContext;
        std::thread mContextThread;

        // The acceptor awaits for incoming messages
        TcpAcceptor mAcceptor;

        // An ID counter for identifying clients
        uint32_t mIdCounter = 10000;


    };
}
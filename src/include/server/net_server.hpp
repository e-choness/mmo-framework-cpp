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
            mAcceptor.async_accept([this](ErrorCode errorCode, TcpSocket socket){
                if(!errorCode){
                    // No error logic
                    std::cout << "[Server] Accept connection: " << socket.remote_endpoint() << "\n";

                    auto newConnection = std::make_shared<Connection<T>>(Connection<T>::Owner::Server, mContext, std::move(socket), mMessagesIn);

                    if(onClientConnect(newConnection)){
                        // Connection allowed, put it in the queue
                        mConnections.push_back(newConnection);

                        mConnections.back()->connectToServer(mIdCounter++);

                        std::cout << "[" << mConnections.back()->getId() << "] Connection Approved.\n";
                    }else{
                        std::cout << "[Server] Connection denied.\n";
                    }
                }else{
                    // Resolve error during acceptance
                    std::cout << "[Server] Accept connection error: " << errorCode.message() << "\n";
                }

                // Wait for another connection
                waitForClientAsync();
            });
        }

        void messageClient(std::shared_ptr<Connection<T>> client, const Message<T>& message){
            if(client && client->isConnected()){
                client->send(message);
            }else{
                onClientConnect(client);
                client.reset();
                mConnections.erase(std::remove(mConnections.begin(), mConnections.end(), client), mConnections.end());
            }
        }

        void messageAllClients(const Message<T>& message, std::shared_ptr<Connection<T>> ignoreClient = nullptr){
            bool hasInvalidClient = false;

            for(auto& client : mConnections){
                if(client && client->isConnected()){
                    if(client != ignoreClient) client->send(message);
                }else{
                    onClientDisconnect(client);
                    client.reset();
                    hasInvalidClient = true;
                }
            }

            if(hasInvalidClient)
                mConnections.erase(std::remove(mConnections.begin(), mConnections.end(), nullptr), mConnections.end());
        }

        void update(size_t maxMessageCount = -1){
            size_t count = 0;
            while(maxMessageCount < count && !mConnections.empty()){
                auto message = mMessagesIn.pop_front();

                onMessage(message.mRemote, message.mMessage);

                count++;
            }
        }
    protected:
        virtual bool onClientConnect(std::shared_ptr<Connection<T>> client){
            return false;
        }

        virtual void onClientDisconnect(std::shared_ptr<Connection<T>> client){

        }

        virtual void onMessage(std::shared_ptr<Connection<T>> client, const Message<T>& message){

        }
    protected:
        // Thread safe queue for incoming messages
        TSQueue<OwnedMessage<T>> mMessagesIn;

        // Queue for active validated connections
        std::deque<std::shared_ptr<Connection<T>>> mConnections;

        // IO context for asio acceptor and socket
        IoContext  mContext;
        std::thread mContextThread;

        // The acceptor awaits for incoming messages
        TcpAcceptor mAcceptor;

        // An ID counter for identifying clients
        uint32_t mIdCounter = 10000;


    };
}
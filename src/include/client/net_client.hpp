#pragma once
#include "net_message.hpp"
#include "net_ts_queue.hpp"
#include "net_connection.hpp"

namespace network{
    template<typename T>
    class ClientInterface{
    public:
        ClientInterface() = default;
        virtual ~ClientInterface(){
            // Disconnect from the server when the client app is destroyed.
            disconnect();
        }

    public:
        // Connect to the server with a hostname or an ip address and a port
        bool connect(const std::string& host, const uint16_t port){
            try{
                // Resolve hostname or ip address into machine-readable address
                TcpResolver resolver(mContext);
                auto endpoints = resolver.resolve(host, std::to_string(port));

                // Create a connection and giving its address to a unique pointer
                mConnection = std::make_unique<Connection<T>>(
                        Connection<T>::Owner::Client,
                        mContext,
                        TcpSocket(mContext),
                        mMessagesIn);

                // Tell the connection object to connect to server
                mConnection->connectToServer(endpoints);

                // Start a thread for running io context
                mContextThread = std::thread([this](){ mContext. run(); });

            }catch (std::exception& e){
                std::cerr << "Client Exception: " << e.what() << "\n";
                return false;
            }
            return true;
        }

        // Disconnect from the server
        void disconnect(){
            // Disconnect the connection if any exists
            if(isConnected()) mConnection->disconnect();

            // Stop the io context anyway
            mContext.stop();

            // Join the context thread if it is join-able
            if(mContextThread.joinable()) mContextThread.join();

            // Destroy the connection
            mConnection.release();
        }

        // Check if it is connected to a server
        bool isConnected(){
            if(mConnection) return mConnection->isConnected();
            else return false;
        }

        void send(const Message<T>& message){
            mConnection->send(message);
        }

        TSQueue<OwnedMessage<T>>& incoming(){
            return mMessagesIn;
        }

    protected:
        // The context handles the data transfer...
        IoContext mContext;

        // A thread to run work commands
        std::thread mContextThread;

        // The unique pointer of a Connection that handles data transfer
        std::unique_ptr<Connection<T>> mConnection;

    private:
        // The thread safe queue for incoming messages from the server
        TSQueue<OwnedMessage<T>> mMessagesIn;
    };
}
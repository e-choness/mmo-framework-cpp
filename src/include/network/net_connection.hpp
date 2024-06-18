#pragma once
#include "std_common.hpp"
#include "net_ts_queue.hpp"
#include "asio_definitions.hpp"
#include "net_message.hpp"

namespace network{
    template<typename T>
    class Connection : public std::enable_shared_from_this<Connection<T>>{
    public:
        enum class Owner{
            Server,
            Client
        };

        // Constructor
        Connection(Owner parent, IoContext& context, TcpSocket socket, TSQueue<OwnedMessage<T>>& messageIn):
        mContext(context), mSocket(std::move(socket)), mMessagesIn(messageIn){
            mOwner = parent;
        }

        // Deconstruct
        virtual ~Connection(){}


        uint32_t getId() const { return mId; }

    public:
        void connectToServer(uint32_t id = 0){ mId = id; }

        void connectToClient(uint32_t id = 0){
            if(mOwner == Owner::Server){
                if(mSocket.is_open())
                    mId = id;
            }
        }
        bool disconnect();

        bool isConnected() const{
            return mSocket.is_open();
        }
    public:
        bool send(const Message<T>& message);

    protected:
        // Connection unique ID
        uint32_t mId = 0;

        // Owner type
        Owner mOwner = Owner::Server;

        // Each connection has a unique socket to a remote
        TcpSocket mSocket;
        // This context is shared with the entire asio instance, provided by either client or server
        IoContext& mContext;

        // A queue holds all messages out to the remote endpoints from this connection
        TSQueue<Message<T>> mMessagesOut;

        // A queue holds all messages come in from the remote endpoints to this connection
        TSQueue<OwnedMessage<T>>& mMessagesIn;
    };
}
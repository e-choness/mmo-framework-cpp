#pragma once
#include "std_common.hpp"
#include "net_ts_queue.hpp"
#include "asio_definitions.hpp"
#include "net_message.hpp"

namespace network{
    template<typename T>
    class Connection : public std::enable_shared_from_this<Connection<T>>{
    public:
        // Constructor
        Connection(){}

        // Deconstruct
        virtual ~Connection(){}
    public:
        bool ConnectToServer();
        bool Disconnect();
        bool IsConnected() const;
    public:
        bool Send(const Message<T>& message);

    protected:
        // Each connection has a unique socket to a remote
        TcpSocket mSocket;
        // This context is shared with the entire asio instance, provided by either client or server
        IoContext& mContext;

        // A queue holds all messages out to the remote endpoints from this connection
        TSQueue<Message<T>> mMessageOut;

        // A queue holds all messages come in from the remote endpoints to this connection
        TSQueue<OwnedMessage<T>>& mMessageIn;
    };
}
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
        virtual ~Connection()= default;


        [[nodiscard]] uint32_t getId() const { return mId; }

    public:
        void connectToServer(ResultType& endpoints){
            if(mOwner == Owner::Client){
                connectAsync(mSocket, endpoints,
                             [this](ErrorCode errorCode, TcpEndpoint endpoint){
                    if(!errorCode){
                        readHeaderAsync();
                    }else{
                        std::cout << "[" << mId << "] failed to connect to the server.\n";
                    }

                });
            }
        }

        void connectToClient(uint32_t id = 0){
            if(mOwner == Owner::Server){
                if(mSocket.is_open())
                {
                    mId = id;
                    readHeaderAsync();
                }
            }
        }
        void disconnect(){
            if(isConnected())
                post(mContext, [this](){ mSocket.close();});
        }

        [[nodiscard]] bool isConnected() const{
            return mSocket.is_open();
        }
    public:
        void send(const Message<T>& message) {
            post(mContext, [this, message](){
                auto isWriting = !mMessagesOut.isEmpty();
                mMessagesOut.pushBack(message);

                // If the io context is already writing into headers, return instead of writing another header that will result in out-of-order messages.
                if(isWriting) return;

                writeHeaderAsync();
            });
        }

    private:
        // Prime context to read a message header
        void readHeaderAsync(){
            asyncRead(mSocket, mTempMsgIn.mHeader, [this](ErrorCode errorCode, size_t length){
                if(!errorCode){
                    if(mTempMsgIn.mHeader.mSize > 0){
                        mTempMsgIn.mBody.resize(mTempMsgIn.mHeader.mSize);
                        readBodyAsync();
                    }else{
                        addToMessagesIn();
                    }
                }else{
                    std::cout << "[" << mId << "] failed to read the message header.\n";
                    mSocket.close();
                }
            });
        }

        // Prime context to read a message body
        void readBodyAsync(){
            asyncReadContainer(mSocket, mTempMsgIn.mBody, [this](ErrorCode errorCode, size_t length){
                if(!errorCode){
                    addToMessagesIn();
                }else{
                    std::cout << "[" << mId << "] failed to read the message body.\n";
                    mSocket.close();
                }
            });
        }

        void writeHeaderAsync(){
            asyncWrite(mSocket, mMessagesOut.front().mHeader,
                      [this](ErrorCode errorCode, size_t length){
                                if(!errorCode){
                                    // No error logic here
                                    if(mMessagesOut.front().mBody.size() > 0){
                                        writeBodyAsync();
                                    }else{
                                        mMessagesOut.popFront();

                                        if(!mMessagesOut.isEmpty()){
                                            writeHeaderAsync();
                                        }
                                    }
                                }else{
                                    std::cout << "[" << mId << "] failed to write the header.\n";
                                    mSocket.close();
                                }
            });
        }

        void writeBodyAsync(){
            asyncWriteContainer(mSocket, mMessagesOut.front().mBody,
                               [this](ErrorCode errorCode, size_t length){
                                        if(!errorCode){
                                            mMessagesOut.popFront();

                                            if(!mMessagesOut.isEmpty()){
                                                writeHeaderAsync();
                                            }
                                        }else{
                                            std::cout << "[" << mId << "] failed to wirte the body.\n";
                                            mSocket.close();
                                        }
            });
        }

        void addToMessagesIn(){
            if(mOwner == Owner::Server){
                mMessagesIn.pushBack({this->shared_from_this(), mTempMsgIn});
            }

            if(mOwner == Owner::Client){
                mMessagesIn.pushBack({nullptr, mTempMsgIn});
            }

            readHeaderAsync();
        }


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
        Message<T> mTempMsgIn;
    };
}
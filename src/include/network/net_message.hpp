#pragma once
#include "std_common.hpp"
#include "net_connection.hpp"

namespace network{
    template <typename T>
    struct MessageHeader{
        T mId{};
        uint32_t mSize = 0;
    };

    template <typename T>
    struct Message{
        MessageHeader<T> mHeader{};
        std::vector<uint8_t> mBody;

        // Get the size of the entire mMessage packet in bytes
        [[nodiscard]] size_t size() const{
            return sizeof(MessageHeader<T>) + mBody.size();
        }

        // ostream << operator override, make it compatible with std::cout
        friend std::ostream& operator<< (std::ostream& os, const Message<T> message){
            os << "ID: " << int(message.mHeader.mId) << " Size: " << message.mHeader.mSize;
            return os;
        }

        // Message<T> << operator override, push data to the mMessage body
        template<typename DataType>
        friend Message<T>& operator<< (Message<T>& message, const DataType& data){
            // Check if it's trivial type
            static_assert(std::is_standard_layout<DataType>::value, "Data is not a trivial type, cannot be pushed into the vector.");

            // Cache the vector size, also the start point to insert data
            size_t size = message.mBody.size();

            // Resize mMessage body for new data
            message.mBody.resize(message.mBody.size() + sizeof(DataType));

            // Copy the data into new vector space
            std::memcpy(message.mBody.data() + size, &data, sizeof(DataType));

            // Give the new size to the header
            message.mHeader.mSize = message.size();

            return message;
        }

        template<typename DataType>
        friend Message<T>& operator>>(Message<T>& message, DataType& data){
            // Check if it's trivial type
            static_assert(std::is_standard_layout<DataType>::value, "Data is not a trivial type, cannot be read from the vector.");

            // Cache the vector size, also the start point to extract data
            size_t size = message.mBody.size() - sizeof(DataType);

            // Copy the data from the vector
            std::memcpy(&data, message.mBody.data() + size, sizeof(DataType));

            // Shrink the vector to remove read bytes
            message.mBody.resize(size);

            // Give updated size to the header
            message.mHeader.mSize = message.size();

            return message;
        }
    };

    template<typename T>
    struct OwnedMessage{
        std::shared_ptr<Connection<T>> mRemote = nullptr;
        Message<T> mMessage;

        friend std::ostream& operator<<(std::ostream& os, const OwnedMessage<T>& message){
            os << message.mMessage;
            return os;
        }
    };
}
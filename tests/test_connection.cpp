//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//#include <boost/asio.hpp>
//#include "net_message.hpp"
//#include "net_ts_queue.hpp"
//#include "Connection.hpp"
//
//using namespace network;
//using namespace boost::asio;
//
//class MockMessage {
//public:
//    MockMessage() : mHeader{0, 0}, mBody{} {}
//    MessageHeader<int> mHeader;
//    std::vector<uint8_t> mBody;
//};
//
//class MockContext : public io_context {};
//
//class MockSocket : public ip::tcp::socket {
//public:
//    MockSocket(MockContext& context) : ip::tcp::socket(context) {}
//};
//
//class ConnectionTest : public ::testing::Test {
//protected:
//    void SetUp() override {
//        mockContext = std::make_shared<MockContext>();
//        mockSocket = std::make_shared<MockSocket>(*mockContext);
//        connection = std::make_shared<Connection<int>>(Connection<int>::Owner::Client, *mockContext, std::move(*mockSocket), messageQueue);
//    }
//
//    void TearDown() override {
//        connection->disconnect();
//    }
//
//    std::shared_ptr<MockContext> mockContext;
//    std::shared_ptr<MockSocket> mockSocket;
//    TSQueue<OwnedMessage<int>> messageQueue;
//    std::shared_ptr<Connection<int>> connection;
//};
//
//TEST_F(ConnectionTest, ConnectToServer) {
//ASSERT_FALSE(connection->isConnected());
//connection->connectToServer(ip::tcp::resolver::results_type{});
//// Simulate asynchronous connect completion
//mockContext->run();
//ASSERT_TRUE(connection->isConnected());
//}
//
//TEST_F(ConnectionTest, ConnectToClient) {
//ASSERT_FALSE(connection->isConnected());
//connection->connectToClient(1);
//ASSERT_TRUE(connection->isConnected());
//}
//
//TEST_F(ConnectionTest, Disconnect) {
//connection->connectToClient(1);
//ASSERT_TRUE(connection->isConnected());
//connection->disconnect();
//mockContext->run();
//ASSERT_FALSE(connection->isConnected());
//}
//
//TEST_F(ConnectionTest, SendMessage) {
//MockMessage message;
//message.mHeader.mId = 1;
//connection->send(message);
//mockContext->run();
//ASSERT_FALSE(messageQueue.isEmpty());
//auto sentMessage = messageQueue.popFront();
//ASSERT_EQ(sentMessage.mHeader.mId, 1);
//}
//
//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}

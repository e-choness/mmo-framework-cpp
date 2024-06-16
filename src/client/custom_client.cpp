#include "custom_client.hpp"


//client::CustomClient::CustomClient() : mBuffer(10 * 1024) {
//
//    }
//
//void client::CustomClient::run() {
//    ErrorCode errorCode;
//
//    // Create a context where the platform specific interface
//    IoContext context;
//
//    // Keep context busy
//    ContextWork idleWork(context);
//
//    // Start the context
//    std::thread contextThread = std::thread([&]() {context.run();});
//
//    // Some IP addresses to experiment on
//    std::string Ip1 = "93.184.216.34";
//    std::string Ip2 = "51.38.81.49";
//    // Grab an endpoint for this one to connect to
//    TcpEndpoint endpoint(make_address(Ip2, errorCode), 80);
//
//    // Create a socket and add context to run the underlying implementation
//    TcpSocket socket(context);
//
//    // RE
//    errorCode = socket.connect(endpoint, errorCode);
//
//    // Process
//    std::string feedback;
//    feedback = ( !errorCode) ? "Connected!\n" : "Failed to connect to address.\n" + errorCode.message();
//    std::cout << feedback;
//
//    if(socket.is_open()){
//
//        // Prime the context before grab data from the website
//        grabAsync(socket);
//
//        std::string request =
//                "GET /index.html HTTP/1.1\r\n"
//                "Host: example.com\r\n"
//                "Connection: close\r\n\r\n";
//
//        socket.write_some(make_buffer(request), errorCode);
//
//        // Wait excessive long for completely  grabbing data from the website
//        using namespace std::chrono_literals;
//        std::this_thread::sleep_for(20000ms);
//
//        context.stop();
//        if(contextThread.joinable()) contextThread.join();
//    }
//}
//
//void client::CustomClient::grabAsync(TcpSocket &socket) {
//    socket.async_read_some(make_buffer(mBuffer),
//                           [&](ErrorCode errorCode, size_t length){
//                               if(!errorCode){
//                                   std::cout << "\n\nRead " << length << " bytes\n";
//                                   for(auto& c : mBuffer) std::cout << c;
//                                   grabAsync(socket);
//                               }
//                           });
//}

client::CustomClient::~CustomClient() {

}

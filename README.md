# A Simple Server-Client Chat App

## About The Project

This is a simple server client app for gracefully handle messsages, sessions and connections.

Following *Dmytro Radchuk*'s [*Boost.Asio C++ Network Programming Cookbook*](https://www.amazon.ca/Boost-Asio-Network-Programming-Cookbook-hands/dp/1783986549) for understanding C++ network programming using Boost Asio.

## Dependencies

- [Boost Asio](https://think-async.com/Asio/](https://www.boost.org/users/download/)https://www.boost.org/users/download/)

## Package Manager
I have done my fair share of CMAKE, will dive into it deeper when the time comes. Right now the package manager combination that has saved my life and time are:

- [Conan](https://github.com/conan-io/conan)
- [CLion](https://www.jetbrains.com/clion/)
- [Conon Clion Plugin](https://plugins.jetbrains.com/plugin/11956-conan)

Highly recommend.

### Part I - Endpoints, Protocols

With Boost Asio TCP and UDP using the same data structure so that they are interchangeable.

- `boost::asio::ip::tcp::endpoint` can be swapped out by `boost::asio::ip::udp::endpoint` if required protocol needs to change.

IP addresses in Boost Asio can be found in the `boost::asio::ip` namespace.

- `boost::asio::ip::address` is agnostic to either `boost::asio::ip::address_v4` or `boost::asio::ip::address_v6`


### Part II - IO Service

`boost::asio::io_service` is required to instantiate before passing it to a socket.

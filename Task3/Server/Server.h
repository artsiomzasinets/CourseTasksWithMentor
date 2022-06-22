//
// Created by artom on 29.04.2022.
//

#ifndef SERVER_H_
#define SERVER_H_

#include <boost/asio.hpp>

#include <iostream>
#include <array>
#include <algorithm>
#include <stdint.h>
#include <thread>

#include "../Currency/Currency.h"





class Server {
private:
    const uint16_t sizeOfClientQueue = 10;
    boost::asio::io_context& ioContext;
    boost::system::error_code errorCode;
    uint16_t portNumber;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::acceptor acceptor;

    std::array<uint8_t,1024> arrayBuffer;
private:
    inline  void processClientsRequest();
    void acceptClient( );
public:
    Server(boost::asio::io_context&, uint16_t );
    void run();
};


#endif //SERVER_H_

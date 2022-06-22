//
// Created by artom on 6/17/2022.
//

#ifndef INC_B3D3D88E8FAE4CAF91A4E7DA638B857D
#define INC_B3D3D88E8FAE4CAF91A4E7DA638B857D

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

#include <iostream>
#include <vector>
#include <thread>

//#define DEBUG

class client: boost::noncopyable{
public:
    client(boost::asio::ip::tcp::endpoint&,boost::asio::io_context&);
    ~client();
    std::vector<uint8_t> sendAndReturnResult(uint64_t ,uint16_t);
private:
    void readData( std::vector<uint8_t>&);//async read
private:
    boost::asio::io_context& ioContext;
    boost::asio::ip::tcp::endpoint& endpoint;
    boost::system::error_code errorCode;
    boost::asio::ip::tcp::socket socket;
};


#endif //INC_B3D3D88E8FAE4CAF91A4E7DA638B857D

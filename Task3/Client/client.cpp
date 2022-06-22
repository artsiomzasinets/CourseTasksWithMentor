//
// Created by artom on 6/17/2022.
//

#include "client.h"


client::client(boost::asio::ip::tcp::endpoint &endP, boost::asio::io_context &context) :
        endpoint(endP), socket(context), ioContext(context){
}

client::~client(){
    socket.close();
}

std::vector<uint8_t> client::sendAndReturnResult(uint64_t numberOfMoney, uint16_t value){
    std::vector<uint8_t> vBuffer(1024);
    std::string request = std::to_string(value) + ' ' + std::to_string(numberOfMoney);
    if(!socket.is_open()){
        socket.connect(endpoint, errorCode);
    }
    if(errorCode){
        std::cout << "Error!Can't connect!Message:" << errorCode.message() << std::endl;
    }else{
#ifdef DEBUG
        std::cout << "Connected and the socket is open" << std::endl;
#endif
        readData(vBuffer);// async read
        socket.write_some(boost::asio::buffer(request.data(), request.size()), errorCode);
        if(errorCode){
            std::cout << "Error!Can't write!Message:" << errorCode.message() << std::endl;
        }

    }


    ioContext.run();// if there is any async function ioService.run() will wait when every function end works
    return vBuffer;
}

void client::readData(std::vector<uint8_t> &vBuffer){//async read
    boost::asio::async_read(socket, boost::asio::buffer(vBuffer.data(), vBuffer.size()),
                            [this, &vBuffer](boost::system::error_code error, uint32_t length){
                                if(error){
#ifdef DEBUG
                                        std::cout << "Failed. Message: " << errorCode.message() << std::endl;
#endif
                                }else{
#ifdef DEBUG
                                    std::cout << "\nRead " << length << " bytes. Message: ";
                                    for(auto i: vBuffer){
                                        std::cout << i;
                                    }
#endif
                                    readData(vBuffer);
                                }
                            });
}

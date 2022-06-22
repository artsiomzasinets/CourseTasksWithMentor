//
// Created by artom on 29.04.2022.
//

#include "Server.h"

Server::Server(boost::asio::io_context & ioCont, uint16_t portNum): ioContext(ioCont),portNumber(portNum),
acceptor(ioContext, endpoint.protocol()),endpoint(boost::asio::ip::address_v4::any(), portNumber){
}



inline void Server::processClientsRequest(){
    std::string temp{};
    std::for_each(arrayBuffer.begin() + 2, arrayBuffer.end(),[&temp](auto elem){
        temp += elem;
    });
    double value = std::atof(temp.c_str());
    temp.clear();
    switch(arrayBuffer[0]){
        case '1': //usd
            temp += Currency::convertor(value,Value::USD);
            break;
        case '2': // eur
            temp += Currency::convertor(value,Value::EUR);
            break;
        case '3'://byr
            temp += Currency::convertor(value,Value::BYR);
            break;
        case '4'://rub
            temp += Currency::convertor(value,Value::RUB);
            break;
        case '5'://uah
            temp += Currency::convertor(value,Value::UAH);
            break;
        case '6'://pln
            temp += Currency::convertor(value,Value::PLN);
            break;
    }
    temp+='\0';
    std::copy(temp.begin(), temp.end(), arrayBuffer.begin());
}


void Server::run(){
    acceptor.bind(endpoint);
    acceptor.listen(sizeOfClientQueue);
    boost::asio::ip::tcp::socket socket(ioContext);
    acceptor.accept(socket);
    socket.read_some(boost::asio::buffer(arrayBuffer.data(), arrayBuffer.size()),errorCode);
    if(errorCode){
        std::cout << "Error in read part!Message:" << errorCode.message() << std::endl;
    }else{
        processClientsRequest();
        socket.write_some(boost::asio::buffer(arrayBuffer.data(), arrayBuffer.size()),errorCode);
        if(errorCode){
            std::cout << "Error in write part!Message:" << errorCode.message() << std::endl;
        }
    }

}







#include "client.h"


const char* ipAddress = "127.0.0.1";
const short portNumber = 8080;

int main(int argc, char *argv[]){
    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(ipAddress),
                                            portNumber);
    client clientConnection(endpoint, ioContext);
    while(true){
        std::cout << "Enter number of money:";
        int number;
        std::cin >> number;
        std::cout << "\t\tChoose currency\n1-USD\n2-EUR\n3-BYR\n4-RUB\n5-UAH\n6-PLN\n7-exit\nChoose(1-7):";
        int choice;
        std::cin >> choice;
        if(choice >= 1 && choice <=7){
            if(choice == 7){
                break;
            }
            auto result = clientConnection.sendAndReturnResult(number,choice);
            std::cout << '\n';
            for(auto i : result){
                if(i == '\0')
                    break;
                std::cout << i;
            }
            std::cout << std::endl;
        }
    }



}
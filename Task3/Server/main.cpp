#include "Server.h"

int main(int argc, char* argv[])
{
    uint16_t port = 8080;
    try{
        boost::asio::io_context ioContext;

        Server server(ioContext,port);
        server.run();

    }catch (std::exception err){
        std::cerr << "Error" << err.what() << std::endl;
    }catch (...){
        std::cerr << "Something unexpected happened" << std::endl;
    }



    return 0;
}
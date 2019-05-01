#include "MockUpSocketClient.hpp"
#include "SocketClient.hpp"

#include <iostream>

MockUpSocketClient::MockUpSocketClient(ServerConnectionInfo& i, SocketClientListener& l)
    : SocketClient(i, l) {

}

MockUpSocketClient::~MockUpSocketClient(){

}

// -----------------------------------
// SocketClient Implementation
// -----------------------------------
void MockUpSocketClient::connect(){
    std::cout << "MockUpSocketClient::connect()\n";
}

void MockUpSocketClient::disconnect(){
    std::cout << "MockUpSocketClient::disconnect()\n";
}

void MockUpSocketClient::send(proto::PContainer& message){
    std::cout << "MockUpSocketClient::send()\n";
    listener.onMessage(message);
}

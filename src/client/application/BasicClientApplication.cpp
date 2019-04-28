#include "BasicClientApplication.hpp"

#include "../../generated/bicyclade.pb.h"

#include <iostream>
#include <string>

BasicClientApplication::BasicClientApplication()
    : ClientApplication(),
      SocketClientListener(),
      lobby(NULL),
      game(NULL),
      socket(NULL) {
}

BasicClientApplication::~BasicClientApplication(){
    delete game;
    game = NULL;
    delete lobby;
    lobby = NULL;
    delete socket;
    socket = NULL;
}

void BasicClientApplication::setSocket(SocketClient* s){
    socket = s;
}

// -----------------------------------
// ClientApplication Implementation
// -----------------------------------
void BasicClientApplication::start(){
    if(socket != NULL){
        socket->connect();
    }
}

void BasicClientApplication::stop(){
    if(socket != NULL){
        socket->disconnect();
    }
}

LobbyClientController* BasicClientApplication::getLobbyController(){
    return lobby;
}

GameClientController* BasicClientApplication::getGameController(){
    return game;
}

// -----------------------------------
// SocketClientListener Implementation
// -----------------------------------
void BasicClientApplication::onOpen(){
    lobby = new BasicLobbyClient(*socket);
    std::cout << "ClientApplication -- Connection Opened\n";
}

void BasicClientApplication::onClose(){
    delete lobby;
    lobby = NULL;
    std::cout << "ClientApplication -- Connection Closed\n";
    // **Warning:** this thread can't delete socket because it will be run in a socket working thread...
}

void BasicClientApplication::onMessage(proto::PContainer& message){
    std::string s;
    message.SerializeToString(&s);
    std::cout << "ClientApplication -- onMessage(): New message: "<< s << "\n";
}

void BasicClientApplication::onFail(){
    /* TODO: Not Implemented Yet */
    std::cout << "ClientApplication -- onFail() \n";
}

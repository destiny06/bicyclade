#include "../../generated/bicyclade.pb.h"
#include "BasicLobbyClient.hpp"

BasicLobbyClient::BasicLobbyClient(SocketClient& s)
    : LobbyClientListener(),
      LobbyClientController(),
      socket(s),
      clientName(NULL) {
}

BasicLobbyClient::~BasicLobbyClient(){

}

// -----------------------------------
// LobbyClientListener Implementation
// -----------------------------------
void BasicLobbyClient::onJoin(){
    /* TODO: Not Implemented Yet */
}

void BasicLobbyClient::onQuit(){
    /* TODO: Not Implemented Yet */
}

void BasicLobbyClient::onRename(){
    /* TODO: Not Implemented Yet */
}

void BasicLobbyClient::onChat(){
    /* TODO: Not Implemented Yet */
}

// -----------------------------------
// LobbyClientController Implementation
// -----------------------------------
void BasicLobbyClient::join(){
    /* TODO: PContainer namespace */
    proto::PContainer message;
    message.set_global_action(proto::PGlobalActionType::CLIENT_ACTION);
    // Client Action
    PClientAction *action = new PClientAction();
    action->set_type(PClientActionType::JOIN_GAME);
    message.set_allocated_client_action(action);        // take ownership and will free itself
    socket.send(message);
}

void BasicLobbyClient::quit(){
    proto::PContainer message;
    message.set_global_action(proto::PGlobalActionType::CLIENT_ACTION);
    // Client Action
    PClientAction *action = new PClientAction();
    action->set_type(PClientActionType::QUIT_GAME);
    if(clientName != NULL){
        action->set_allocated_name(new std::string(*clientName));    // take ownership and will free itself
    }
    message.set_allocated_client_action(action);        // take ownership and will free itself
    socket.send(message);
}

void BasicLobbyClient::rename(std::string& name){
    proto::PContainer message;
    message.set_global_action(proto::PGlobalActionType::CLIENT_ACTION);
    // Client Action
    PClientAction *action = new PClientAction();
    action->set_type(PClientActionType::ADD_NAME);
    action->set_allocated_name(new std::string(name));  // take ownership and will free itself
    message.set_allocated_client_action(action);        // take ownership and will free itself
    socket.send(message);
}

void BasicLobbyClient::chat(std::string& chatMsg){
    proto::PContainer message;
    message.set_global_action(proto::PGlobalActionType::CLIENT_ACTION);
    // Client Action
    PClientAction *action = new PClientAction();
    action->set_type(PClientActionType::CHAT);
    if(clientName != NULL){
        action->set_allocated_name(new std::string(*clientName));    // take ownership and will free itself
    }
    PAction_CHAT *chatMessage = new PAction_CHAT(); // TODO: Inconsistency in naming CASE
    chatMessage->set_allocated_message(new std::string(chatMsg)); // take ownership and will free itself
    action->set_allocated_action_chat(chatMessage);     // take ownership and will free itself
    message.set_allocated_client_action(action);        // take ownership and will free itself
    socket.send(message);
}


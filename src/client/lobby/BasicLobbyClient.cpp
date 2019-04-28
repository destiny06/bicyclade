#include "../../generated/bicyclade.pb.h"
#include "BasicLobbyClient.hpp"

#include <iostream>

BasicLobbyClient::BasicLobbyClient(SocketClient& s)
    : LobbyClientController(),
      socket(s),
      myself(NULL),
      externalListener(NULL) {

    /* TODO: Workaround waiting for JOIN_GAME implementation */
    clients.push_back(Client(0,"Nobody"));
}

BasicLobbyClient::~BasicLobbyClient(){

}

void BasicLobbyClient::setExternalListener(LobbyClientListener* listener){
    externalListener = listener;
}

void BasicLobbyClient::onClientAction(const PClientAction& action){
    switch(action.type())
    {
    case PClientActionType::JOIN_GAME:
        {
            /* TODO: Workaround waiting for JOIN_GAME implementation */
            Client *client = retrieveClientFromName("Nobody");
            if(client == NULL){
                std::cout << "Error: could not find any client with this name.\n";
                break;
            }

            // Forward to external listener if any
            if(externalListener != NULL){
                externalListener->onJoin(*client);
            }
        }
        break;
    case PClientActionType::ADD_NAME:
        {
            /* TODO: Workaround, should be in JOIN_GAME */
            clients.push_back(Client(0, action.name())); /* TODO: Implement ID */
            Client *client = retrieveClientFromName(action.name());
            if(client == NULL){
                std::cout << "Error: could not find any client with this name.\n";
                break;
            }

            // If there is a pending rename, update myself variable
            if(pendingRename == client->name){
                myself = client;
                pendingRename = ""; /* TODO: could break with empty client name. Must be forbidden. */
            }

            // Forward to external listener if any
            if(externalListener != NULL){
                externalListener->onRename(*client, "Not Implemented Yet"); /* TODO: Workaround */
            }
        }
        break;
    case PClientActionType::CHAT:
        {
            Client *client = retrieveClientFromName(action.name());
            if(client == NULL){
                std::cout << "Error: could not find any client with this name.\n";
                break;
            }

            // Forward to external listener if any
            if(externalListener != NULL){
                externalListener->onChat(*client, action.action_chat().message());
            }
        }
        break;
    case PClientActionType::QUIT_GAME:
        {
            Client *client = retrieveClientFromName(action.name());

            if(client == NULL){
                std::cout << "Error: could not find any client with this name.\n";
                break;
            }

            // Forward to external listener if any
            if(externalListener != NULL){
                externalListener->onQuit(*client);
            }
        }
        break;
    default:
        std::cout << "Error, unknown type (PClientActionType).\n"; // Message is discarded
        break;
    }
}

void BasicLobbyClient::onServerAction(const PServerAction& action){
    /* TODO: Not Implemented Yet */
}


Client* BasicLobbyClient::retrieveClientFromName(const std::string& name){
    for(std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++){
        if(it->name == name){
            return &(*it);
        }
    }
    return NULL;
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
    if(myself != NULL){
        action->set_allocated_name(new std::string(myself->name));    // take ownership and will free itself
    }
    message.set_allocated_client_action(action);        // take ownership and will free itself
    socket.send(message);
}

void BasicLobbyClient::rename(std::string& name){
    pendingRename = name; // We will check a response from the server with this name (TODO: could break if two people try the same name...)

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
    if(myself != NULL){
        action->set_allocated_name(new std::string(myself->name));    // take ownership and will free itself
    }
    PAction_CHAT *chatMessage = new PAction_CHAT(); // TODO: Inconsistency in naming CASE
    chatMessage->set_allocated_message(new std::string(chatMsg)); // take ownership and will free itself
    action->set_allocated_action_chat(chatMessage);     // take ownership and will free itself
    message.set_allocated_client_action(action);        // take ownership and will free itself
    socket.send(message);
}



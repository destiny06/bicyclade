#include "../../generated/bicyclade.pb.h"
#include "BasicLobbyClient.hpp"

#include <iostream>

BasicLobbyClient::BasicLobbyClient(SocketClient& s)
    : LobbyClientController(),
      socket(s),
      myself(NULL),
      externalListener(NULL) {

    /* TODO: Workaround */
    myself = new Client(0,"");
    clients.push_back(myself);
}

BasicLobbyClient::~BasicLobbyClient(){

}

void BasicLobbyClient::setExternalListener(LobbyClientListener* listener){
    externalListener = listener;
}

/* TODO redesign the handling of the clients once new version from the server */
void BasicLobbyClient::onClientAction(const PClientAction& action){
    switch(action.type())
    {
    case PClientActionType::JOIN_GAME:
        {
            /* TODO Basically we can only know players that are joining after we were connected
             * thus we won't know all the potential clients until the game start*/

            /* TODO check that our join worked (similar to add name technic ?)*/

            Client *client = retrieveClientFromName(action.name());

            if (client == nullptr) {
                client = new Client(0, action.name());
                clients.push_back(client); /* TODO: Implement ID */
            }

            // Forward to external listener if any
            if(externalListener != NULL){
                externalListener->onJoin(*client);
            }
        }
        break;
    case PClientActionType::ADD_NAME:
        {
            std::string oldName = "";
            // If there is a pending rename, update myself variable
            if(pendingRename == action.name()){
                oldName = myself->name;
                myself->name = action.name();
                pendingRename = ""; /* TODO: could break with empty client name. Must be forbidden. */
            } else {
                /* TODO error case */
            }

            //Just to send a client to the listener
            Client c(0,action.name());

            // Forward to external listener if any
            if(externalListener != NULL){
                externalListener->onRename(c, oldName); /* TODO: Workaround */
            }
        }
        break;
    case PClientActionType::CHAT:
        {
            Client *client = retrieveClientFromName(action.name());

            if (client == nullptr) {
                client = new Client(0, action.name());
                clients.push_back(client); /* TODO: Implement ID */
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

            if (client == nullptr) {
                Client c(0,action.name());
                client = &c;
            } else {
                /* TODO remove the client from the list if we have it and free the pointer */
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

    std::list<Client*>::iterator it = std::find_if(
    clients.begin(),
    clients.end(),
            [name](const Client* c) {return c->name == name; });

    if (it != clients.end()) {
        return *it;
    } else {
        return NULL;
    }
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



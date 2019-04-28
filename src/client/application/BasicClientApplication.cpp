#include "BasicClientApplication.hpp"

#include "../../generated/bicyclade.pb.h"

#include <iostream>
#include <string>

BasicClientApplication::BasicClientApplication()
    : ClientApplication(),
      SocketClientListener(),
      lobby(NULL),
      game(NULL),
      socket(NULL),
      externalSocketListener(NULL),
      externalLobbyListener(NULL),
      externalGameListener(NULL) {
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

void BasicClientApplication::setExternalSocketListener(SocketClientListener* listener){
    externalSocketListener = listener;
}

void BasicClientApplication::setExternalLobbyListener(LobbyClientListener* listener){
    externalLobbyListener = listener;
    // Also directly update the lobby if instantiated.
    if(lobby != NULL){
        lobby->setExternalListener(listener);
    }
}

void BasicClientApplication::setExternalGameListener(GameClientListener* listener){
    externalGameListener = listener;
    // Also directly update the game if instantiated.
    if(game != NULL){
        game->setExternalListener(listener);
    }
}

// -----------------------------------
// SocketClientListener Implementation
// -----------------------------------
void BasicClientApplication::onOpen(){
    lobby = new BasicLobbyClient(*socket);
    lobby->setExternalListener(externalLobbyListener); // Does work even if pointer is NULL

    // Forward to external listener if any
    if(externalSocketListener != NULL){
        externalSocketListener->onOpen();
    }
}

void BasicClientApplication::onClose(){
    delete lobby;
    lobby = NULL;
    // **Warning:** this thread can't delete socket because it will be run in a socket working thread...

    // Forward to external listener if any
    if(externalSocketListener != NULL){
        externalSocketListener->onClose();
    }
}

void BasicClientApplication::onMessage(proto::PContainer& message){
    switch (message.global_action())
    {
    /* --- Lobby Messages --- */
    case proto::PGlobalActionType::CLIENT_ACTION:
        if(lobby != NULL){
            lobby->onClientAction(message.client_action());
        } else {
            std::cout << "Error: receiving a ClientAction message while no lobby is instantiate to manage it.\n";
        }
        break;
    case proto::PGlobalActionType::SERVER_ACTION:
        if(lobby != NULL){
            lobby->onServerAction(message.server_action());
        } else {
            std::cout << "Error: receiving a ServerAction message while no lobby is instantiate to manage it.\n";
        }
        break;

    /* --- Game Messages --- */
    case proto::PGlobalActionType::PLAYER_ACTION:
        if(game != NULL){
            game->onPlayerAction(message.player_action());
        } else {
            std::cout << "Error: receiving a PlayerAction message while no game is instantiate to manage it.\n";
        }
        break;
    case proto::PGlobalActionType::GAME_ACTION:
        if(game != NULL){
            game->onGameAction(message.game_action());
        } else {
            std::cout << "Error: receiving a GameAction message while no game is instantiate to manage it.\n";
        }
        break;
    default:
        std::cout << "Error, unknown type (PGlobalActionType).\n"; // Message is discarded
        break;
    }

    // Forward to external listener if any
    if(externalSocketListener != NULL){
        externalSocketListener->onMessage(message);
    }
}

void BasicClientApplication::onFail(){
    /* TODO: Not Implemented Yet */

    // Forward to external listener if any
    if(externalSocketListener != NULL){
        externalSocketListener->onFail();
    }
}

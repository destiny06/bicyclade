#include "LobbyController.hpp"

using namespace proto;
using namespace std;

int LobbyController::create_client() {
    Client* c = new Client(nextId++);
    clientsMap.insert(std::make_pair(c->id,c));
    return c->id;
}

void LobbyController::remove_client(int id) {
    clientMapType::iterator itr = clientsMap.find(id);
    delete itr->second;
    clientsMap.erase(itr);
    /* TODO remove from player map as well */
}

void LobbyController::onAddName(ClientAction action) {
    clientMapType::iterator itr = clientsMap.find(action.first);
    Client* c = itr->second;
    c->name = action.second.client_action().name();
}

void LobbyController::onJoinGame(ClientAction action) {
    clientMapType::iterator itr = clientsMap.find(action.first);
    Client* c = itr->second;
    Player* p = new Player(*c);
    playersMap.insert(std::make_pair(c->id,p));
}

playerMapType* LobbyController::getPlayers() {
    return &playersMap;
}

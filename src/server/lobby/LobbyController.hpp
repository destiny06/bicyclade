#pragma once
#include "server/network/WebsocketServer.hpp"
#include "bom/Client.hpp"
#include "bom/Player.hpp"

typedef std::map<int, Client*> clientMapType;
typedef std::map<int, Player*> playerMapType;
typedef std::pair<int,proto::PContainer> ClientAction;

class LobbyController {
private:

    clientMapType clientsMap;
    playerMapType playersMap;

public:

int create_client();
void remove_client(int id);
void onAddName(ClientAction action);
void onJoinGame(ClientAction action);

playerMapType* getPlayers();

};

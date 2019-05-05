#pragma once

#include "bom/Client.hpp"

#include "network/WebsocketServer.hpp"
#include "lobby/LobbyController.hpp"
#include "game/GameController.hpp"

#include <queue>
#include <condition_variable>

using namespace std;

class Server {
private:
    condition_variable actionCondVar;
    std::queue<ClientAction> actionsQueue;
    mutex actionLock;

    WebsocketServer socketServer;
    LobbyController lobby;
    GameController game;

public:

Server() = default;
void start();
int create_client();
void remove_client(int id);
void process_messages();

};

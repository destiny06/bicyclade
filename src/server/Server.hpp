#pragma once

#include "../bom/Client.hpp"

#include "WebsocketServer.hpp"

#include <queue>
#include <condition_variable>

using namespace std;
typedef std::map<int, Client*> clientMapType;

class Server {
private:
    condition_variable actionCondVar;
    std::queue<ClientAction> actionsQueue;
    mutex actionLock;
    WebsocketServer socketServer;
    clientMapType clientsMap;

public:

void start();
int create_client();
void remove_client(int id);
void process_messages();

};

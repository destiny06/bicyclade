#pragma once

#include "../bom/Client.hpp"
#include "../generated/bicyclade.pb.h"

#include "websocket.hpp"

#include <queue>
#include <condition_variable>

using bicyclade::Action;
using namespace std;
typedef std::map<int, Client*> clientMapType;

class Server {
private:
    condition_variable actionCondVar;
    std::queue<Action> actionsQueue;
    mutex actionLock;
    websocketserver socketServer;
    clientMapType clientsMap;

public:

void start();
int create_client();
void remove_client(int id);
void process_messages();

};

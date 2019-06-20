#include "Server.hpp"

#include "bicyclade.pb.h"
#include "serveractions.pb.h"
#include "common.pb.h"
#include "common/Util.hpp"
#include "common/adapter/CppToProto.hpp"

using namespace proto;
using namespace std;

void Server::start() {
    nextId = 0;
    try {
        socketServer.init(&actionCondVar, &actionsQueue, &actionLock, this);
        thread s(bind(&WebsocketServer::run,&socketServer,9002));
        process_messages();
        s.join();
    } catch (websocketpp::exception const & e) {
        cout << e.what() << endl;
    }

}

int Server::create_client() {
    return lobby.create_client();
}

void Server::remove_client(int id) {
    return lobby.remove_client(id);
}

void Server::process_messages() {
    while(1) {
        unique_lock<mutex> lock(actionLock);

        while(actionsQueue.empty())
        {
            actionCondVar.wait(lock);
        }

        ClientAction a = actionsQueue.front();

        switch (a.second.global_action())
        {
        case CLIENT_ACTION:
            switch (a.second.client_action().type())
            {
            case ADD_NAME:
                lobby.onAddName(a);
                socketServer.send(a.first,a.second);
                break;
            case CHAT:
                socketServer.broadcast(a.second);
                break;
            case JOIN_GAME:
                lobby.onJoinGame(a);
                {
                    if (lobby.getPlayers()->size() == 3) {
                        game.startGame(lobby.getPlayers());
                        PContainer c = CppToProto().buildStartGame(lobby.getPlayers());
						socketServer.broadcast(c);
                    }
                    socketServer.send(a.first,a.second);
                }
                break;
            default:
                break;
            }
            break;
            case PLAYER_ACTION:
                /* TODO call game controller */
                break;
            default:
                break;
        }

        actionsQueue.pop();
        lock.unlock();
    }
}

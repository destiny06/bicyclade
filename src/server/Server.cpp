#include "Server.hpp"

#include "../generated/bicyclade.pb.h"
#include "../common/Util.hpp"

using namespace proto;

void Server::start() {
    nextId = 0;
    try {
        socketServer.init(&actionCondVar, &actionsQueue, &actionLock, this);
        thread s(bind(&WebsocketServer::run,&socketServer,9002));
        process_messages();
        s.join();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }

}

int Server::create_client() {
    Client* c = new Client(nextId++);
    clientsMap.insert(std::make_pair(c->id,c));
    return c->id;
}

void Server::remove_client(int id) {
    clientMapType::iterator itr = clientsMap.find(id);
    delete itr->second;
    clientsMap.erase(itr);
}

void Server::process_messages() {
    while(1) {
        unique_lock<mutex> lock(actionLock);

        while(actionsQueue.empty())
        {
            actionCondVar.wait(lock);
        }

        ClientAction a = actionsQueue.front();
        clientMapType::iterator itr = clientsMap.find(a.first);
        Client* c = itr->second;
        switch (a.second.client_action().type())
		{
        case ADD_NAME:
        	c->name = a.second.client_action().name();
        	socketServer.send(a.first,a.second);
        	break;
        case CHAT:
            socketServer.broadcast(a.second);
        	break;
        case JOIN_GAME:
            //TODO
        	break;
        default:
        	break;
        }
        actionsQueue.pop();
        lock.unlock();

    }
}

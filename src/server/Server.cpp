#include "Server.hpp"

#include "../common/Util.hpp"

void Server::start() {
    nextId = 0;
    try {
        socketServer.init(&actionCondVar, &actionsQueue, &actionLock, this);
        thread s(bind(&websocketserver::run,&socketServer,9002));
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

        while(actionsQueue.empty()) {
            actionCondVar.wait(lock);
        }

        Action a = actionsQueue.front();
        actionsQueue.pop();
        lock.unlock();
        socketServer.broadcast(a);
    }
}

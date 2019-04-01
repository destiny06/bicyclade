#pragma once

#include "../generated/bicyclade.pb.h"
#include "../common/Util.hpp"

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

using websocketpp::connection_hdl;
using namespace proto;
using namespace std;

typedef websocketpp::server<websocketpp::config::asio> server;
typedef std::map<connection_hdl,int,std::owner_less<connection_hdl>> connectionMapType;
typedef std::pair<int,PContainer> ClientAction;

class Server;

class WebsocketServer {
private:

    condition_variable* actionCondVar;
	std::queue<ClientAction>* actionsQueue;
    mutex* actionLock;
    Server* mainServer;
    connectionMapType connectionMap;
    server socketServer;

public:

    WebsocketServer();
    void init(condition_variable* actionCondVar, std::queue<ClientAction>* actionsQueue, mutex* actionLock, Server* mainServer);
    void on_open(connection_hdl hdl);
    void on_close(connection_hdl hdl);
    void on_message(connection_hdl hdl, server::message_ptr msg);
    void broadcast(PContainer& action);
    void send(int id, PContainer action);
    void run(uint16_t port);

};

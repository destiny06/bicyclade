#pragma once

#include "../generated/bicyclade.pb.h"
#include "../common/Util.hpp"

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

using websocketpp::connection_hdl;
using bicyclade::Action;
using namespace std;

typedef websocketpp::server<websocketpp::config::asio> server;
typedef std::map<connection_hdl,int,std::owner_less<connection_hdl>> connectionMapType;

class Server;

class websocketserver {
private:

    condition_variable* actionCondVar;
	std::queue<Action>* actionsQueue;
    mutex* actionLock;
    Server* mainServer;
    connectionMapType connectionMap;
    server socketServer;

public:

    websocketserver();
    void init(condition_variable* actionCondVar, std::queue<Action>* actionsQueue, mutex* actionLock, Server* mainServer);
    void on_open(connection_hdl hdl);
    void on_close(connection_hdl hdl);
    void on_message(connection_hdl hdl, server::message_ptr msg);
    void broadcast(Action& action);
    void run(uint16_t port);

};

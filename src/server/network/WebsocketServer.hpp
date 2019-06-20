#pragma once

#include "bicyclade.pb.h"
#include "common/Util.hpp"

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

using websocketpp::connection_hdl;

typedef websocketpp::server<websocketpp::config::asio> server;
typedef std::map<connection_hdl,int,std::owner_less<connection_hdl>> connectionMapType;
typedef std::pair<int,proto::PContainer> ClientAction;

class Server;

class WebsocketServer {
private:

    std::condition_variable* actionCondVar;
	std::queue<ClientAction>* actionsQueue;
    std::mutex* actionLock;
    Server* mainServer;
    connectionMapType connectionMap;
    server socketServer;

public:

    WebsocketServer() = default;
    void init(std::condition_variable* actionCondVar, std::queue<ClientAction>* actionsQueue, std::mutex* actionLock, Server* mainServer);
    void on_open(connection_hdl hdl);
    void on_close(connection_hdl hdl);
    void on_message(connection_hdl hdl, server::message_ptr msg);
    void broadcast(proto::PContainer& action);
    void send(int id, proto::PContainer action);
    void run(uint16_t port);

};

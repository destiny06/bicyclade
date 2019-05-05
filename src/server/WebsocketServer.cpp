#include "WebsocketServer.hpp"

#include "../server/Server.hpp"

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

using namespace std;

WebsocketServer::WebsocketServer() {
}

void WebsocketServer::init(condition_variable* actionCondVar, std::queue<ClientAction>* actionsQueue, mutex* actionLock, Server* mainServer) {

	// Initialize Asio Transport
	socketServer.init_asio();

	// Register handler callbacks
	socketServer.set_open_handler(bind(&WebsocketServer::on_open,this,::_1));
	socketServer.set_close_handler(bind(&WebsocketServer::on_close,this,::_1));
	socketServer.set_message_handler(bind(&WebsocketServer::on_message,this,::_1,::_2));

	this->actionCondVar = actionCondVar;
	this->actionsQueue = actionsQueue;
	this->actionLock = actionLock;
	this->mainServer = mainServer;
}


void WebsocketServer::run(uint16_t port) {
	// listen on specified port
	socketServer.listen(port);

	// Start the server accept loop
	socketServer.start_accept();

	// Start the ASIO io_service run loop
	try {
		socketServer.run();
	} catch (const std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

void WebsocketServer::on_open(connection_hdl hdl) {
	{
	    lock_guard<mutex> guard(*actionLock);
	    int id = mainServer->create_client();
	    connectionMap.insert(std::make_pair(hdl,id));
	}
}

void WebsocketServer::on_close(connection_hdl hdl) {
	{
		lock_guard<mutex> guard(*actionLock);
		//std::cout << "on_close" << std::endl;
		connectionMapType::iterator it = connectionMap.find(hdl);
		mainServer->remove_client(it->second);
		connectionMap.erase(hdl);
	}
}

void WebsocketServer::on_message(connection_hdl hdl, server::message_ptr msg) {
	// queue message up for sending by processing thread
	{
		lock_guard<mutex> guard(*actionLock);
		PContainer con;
		connectionMapType::iterator it = connectionMap.find(hdl);
		con.ParseFromString(msg->get_payload());
		actionsQueue->push(std::make_pair(it->second,con));
	}
	actionCondVar->notify_one();
}

void WebsocketServer::send(int id, PContainer action) {
	connectionMapType::iterator con = std::find_if(
			connectionMap.begin(),
			connectionMap.end(),
			[id](const std::pair<connection_hdl,int>& mo) {return mo.second == id; });

	string sria;
	action.SerializeToString(&sria);
	socketServer.send(con->first,sria,websocketpp::frame::opcode::binary);
}

void WebsocketServer::broadcast(PContainer& action) {
    connectionMapType::iterator it;
	string sria;
	action.SerializeToString(&sria);
	for (it = connectionMap.begin(); it != connectionMap.end(); ++it) {
		socketServer.send(it->first,sria,websocketpp::frame::opcode::binary);
	}
}

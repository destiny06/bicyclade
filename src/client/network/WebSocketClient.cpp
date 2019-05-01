#include "WebSocketClient.hpp"

#include "SocketClient.hpp"
#include "ServerConnectionInfo.hpp"
#include "SocketClientListener.hpp"

#include <iostream>

WebSocketClient::WebSocketClient(ServerConnectionInfo& i, SocketClientListener& l)
    : SocketClient(i, l),
      endpoint(l),
      socketID(-1)
{
}

WebSocketClient::~WebSocketClient(){

}

// -----------------------------------
// SocketClient Implementation
// -----------------------------------
void WebSocketClient::connect(){
    std::string uri = "ws://" + info.host + ":" + info.port;
    std::cout << "[WebSocket-Logger]: Trying to connect to "<< uri <<"\n";
    socketID = endpoint.connect(uri);
}

void WebSocketClient::disconnect(){
    endpoint.close(socketID, websocketpp::close::status::normal, "Bye");
}

void WebSocketClient::send(const proto::PContainer& message){
    string s;
    bool b = message.SerializeToString(&s);

    std::cout << "[WebSocket-Logger]: Sending message: [";
    for(int i=0; i<s.size()-1; i++){
        std::cout << (int) s[i] << "-";
    }
    std::cout << (int) s[s.size()-1] << "], size( "<< s.size() << ")\n";

    endpoint.send(socketID, s);
}

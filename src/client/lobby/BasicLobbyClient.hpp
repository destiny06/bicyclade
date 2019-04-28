#pragma once

#include "LobbyClientListener.hpp"
#include "LobbyClientController.hpp"
#include "../network/SocketClient.hpp"

class BasicLobbyClient : public LobbyClientListener, public LobbyClientController {
private:
    SocketClient& socket;
    std::string *clientName;      // Once validated by the server, NULL otherwise.

public:
    BasicLobbyClient(SocketClient& socket);
    virtual ~BasicLobbyClient();

    // -----------------------------------
    // LobbyClientListener Implementation
    // -----------------------------------
    void onJoin();
    void onQuit();
    void onRename();
    void onChat();

    // -----------------------------------
    // LobbyClientController Implementation
    // -----------------------------------
    void join();
    void quit();
    void rename(std::string& name);
    void chat(std::string& message);
};

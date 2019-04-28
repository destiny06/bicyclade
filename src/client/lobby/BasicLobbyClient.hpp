#pragma once

#include "LobbyClientListener.hpp"
#include "LobbyClientController.hpp"
#include "../network/SocketClient.hpp"
#include "../../bom/Client.hpp"

#include "../../generated/bicyclade.pb.h"

#include <list>

class BasicLobbyClient : public LobbyClientController {
private:
    SocketClient& socket;
    std::string pendingRename;
    Client *myself;     // Once validated by the server, NULL otherwise.
    LobbyClientListener* externalListener;
    std::list<Client> clients;

public:
    BasicLobbyClient(SocketClient& socket);
    virtual ~BasicLobbyClient();

    void setExternalListener(LobbyClientListener* listener);
    void onClientAction(const PClientAction& action);
    void onServerAction(const PServerAction& action);

    // -----------------------------------
    // LobbyClientController Implementation
    // -----------------------------------
    void join();
    void quit();
    void rename(std::string& name);
    void chat(std::string& message);

private:
    Client* retrieveClientFromName(const std::string& name);
};

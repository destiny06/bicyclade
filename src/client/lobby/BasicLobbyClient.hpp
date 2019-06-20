#pragma once

#include "LobbyClientListener.hpp"
#include "LobbyClientController.hpp"
#include "client/network/SocketClient.hpp"
#include "bom/Client.hpp"

#include "bicyclade.pb.h"
#include "clientactions.pb.h"
#include "serveractions.pb.h"

#include <list>

/**
 * Implementation of LobbyClientController used by BasicClientApplication
 *
 * This class is the direct implementation of the communication protocol
 * between the server and the client relative to lobby interactions.
 *
 * This communication is done through Protocol Buffer objects:
 * - PClientAction (lobby action initiated by a client)
 * - PServerAction (lobby action from the server)
 *
 * Specifications of the protocol is documented in the Bicyclades wiki.
 */
class BasicLobbyClient : public LobbyClientController {
private:
    SocketClient& socket;
    std::string pendingRename;
    Client *myself;     // Once validated by the server, NULL otherwise.
    LobbyClientListener* externalListener;
    std::list<Client*> clients;

public:
    BasicLobbyClient(SocketClient& socket);
    virtual ~BasicLobbyClient();

    void setExternalListener(LobbyClientListener* listener);
    void onClientAction(const proto::PClientAction& action);
    void onServerAction(const proto::PServerAction& action);

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

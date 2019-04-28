#pragma once

#include "../lobby/LobbyClientController.hpp"
#include "../lobby/LobbyClientListener.hpp"
#include "../game/GameClientController.hpp"
#include "../game/GameClientListener.hpp"
#include "../network/SocketClient.hpp"

class ClientApplication {
public:
    ClientApplication(){}
    virtual ~ClientApplication(){}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual LobbyClientController* getLobbyController() = 0;
    virtual GameClientController* getGameController() = 0;
    virtual void setExternalSocketListener(SocketClientListener* listener) = 0;
    virtual void setExternalLobbyListener(LobbyClientListener* listener) = 0;
    virtual void setExternalGameListener(GameClientListener* listener) = 0;
};

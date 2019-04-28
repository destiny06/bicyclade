#pragma once

#include "../lobby/LobbyClientController.hpp"
#include "../game/GameClientController.hpp"
#include "../network/SocketClient.hpp"

class ClientApplication {
public:
    ClientApplication(){}
    virtual ~ClientApplication(){}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual LobbyClientController* getLobbyController() = 0;
    virtual GameClientController* getGameController() = 0;
};

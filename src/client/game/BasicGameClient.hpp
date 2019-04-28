#pragma once

#include "GameClientListener.hpp"
#include "GameClientController.hpp"
#include "../network/SocketClient.hpp"

class BasicGameClient : public GameClientListener, public GameClientController {
private:
    SocketClient& socket;

public:
    BasicGameClient(SocketClient& socket);
    virtual ~BasicGameClient();

    // -----------------------------------
    // GameClientListener Implementation
    // -----------------------------------
    void onUpdateCoins();

    // -----------------------------------
    // GameClientController Implementation
    // -----------------------------------
    void putOfferingMarker();
};

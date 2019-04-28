#pragma once

#include "GameClientListener.hpp"
#include "GameClientController.hpp"
#include "../network/SocketClient.hpp"

class BasicGameClient : public GameClientController {
private:
    SocketClient& socket;
    GameClientListener* externalListener;

public:
    BasicGameClient(SocketClient& socket);
    virtual ~BasicGameClient();

    void setExternalListener(GameClientListener* listener);
    void onPlayerAction(const PPlayerAction& action);
    void onGameAction(const PGameAction& action);

    // -----------------------------------
    // GameClientController Implementation
    // -----------------------------------
    void putOfferingMarker();
};

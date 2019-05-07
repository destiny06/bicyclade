#pragma once

#include "GameClientListener.hpp"
#include "GameClientController.hpp"
#include "../network/SocketClient.hpp"

/**
 * Implementation of GameClientController used by BasicClientApplication
 *
 * This class is the direct implementation of the communication protocol
 * between the server and the client relative to game interactions.
 *
 * This communication is done through Protocol Buffer objects:
 * - PPlayerAction (game action initiated by a player)
 * - PGameAction (game action from the game master)
 *
 * Specifications of the protocol is documented in the Bicyclades wiki.
 */
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

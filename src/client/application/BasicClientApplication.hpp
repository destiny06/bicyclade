#pragma once

#include "client/game/BasicGameClient.hpp"
#include "client/network/SocketClient.hpp"
#include "client/lobby/BasicLobbyClient.hpp"

#include "ClientApplication.hpp"

/**
 * Implementation of ClientApplication
 *
 * This class is the direct implementation of the communication protocol
 * between the server and the client through Protocol Buffer object PContainer.
 *
 * Specifications of the protocol is documented in the Bicyclades wiki.
 */
class BasicClientApplication : public ClientApplication, public SocketClientListener {
private:
    SocketClient* socket; /* Owner of the socket, must free it */
    BasicLobbyClient* lobby;
    BasicGameClient* game;
    SocketClientListener* externalSocketListener; /* For debug & tests purpose only */
    LobbyClientListener* externalLobbyListener;
    GameClientListener* externalGameListener;

public:
    BasicClientApplication();
    virtual ~BasicClientApplication();

    /**
     * @param socket: **Warning:** The application will take the ownership of
     * the socket and will free it when needed.
     */
    void setSocket(SocketClient* socket);

    // -----------------------------------
    // ClientApplication Implementation
    // -----------------------------------
    void start();
    void stop();
    LobbyClientController* getLobbyController();
    GameClientController* getGameController();
    void setExternalSocketListener(SocketClientListener* listener);
    void setExternalLobbyListener(LobbyClientListener* listener);
    void setExternalGameListener(GameClientListener* listener);

    // -----------------------------------
    // SocketClientListener Implementation
    // -----------------------------------
    /**
     * The following functions are socket listeners and will be called
     * in a dedicated thread of the socket. Therefore, the socket need to
     * be instantiated and running in order to call those listeners
     * callback functions. Thus, it is not their purpose to allocate or
     * free the socket. This will be done in the start/stop functions.
     */
    void onOpen();
    void onClose();
    void onMessage(const proto::PContainer& message);
    void onFail();
};

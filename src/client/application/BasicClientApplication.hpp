#pragma once

#include "../game/BasicGameClient.hpp"
#include "ClientApplication.hpp"
#include "../network/SocketClient.hpp"
#include "../lobby/BasicLobbyClient.hpp"

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
     * **Warning:** The application will take the ownership of the socket.
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
    void onOpen();
    void onClose();
    void onMessage(proto::PContainer& message);
    void onFail();
};

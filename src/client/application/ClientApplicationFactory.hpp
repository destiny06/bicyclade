#pragma once

#include "ClientApplication.hpp"
#include "BasicClientApplication.hpp"
#include "../network/ServerConnectionInfo.hpp"
#include "../network/WebSocketClient.hpp"

/**
 * Factory for ClientApplication implementations
 */
class ClientApplicationFactory {
public:
    /**
     * Implementation using Websocket as a way to interact with the server.
     *
     * @return **Warning:** The creator will be the owner of the application and
     *  must free it.
     */
    static ClientApplication* CreateWithWebSocket(ServerConnectionInfo& info){
        BasicClientApplication *app = new BasicClientApplication();
        SocketClient *socket = new WebSocketClient(info, *app);
        app->setSocket(socket);
        return app;
    }
};

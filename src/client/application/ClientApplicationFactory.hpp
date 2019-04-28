#pragma once

#include "ClientApplication.hpp"
#include "BasicClientApplication.hpp"
#include "../network/ServerConnectionInfo.hpp"
#include "../network/MockUpSocketClient.hpp"
#include "../network/WebSocketClient.hpp"

class ClientApplicationFactory {
public:
    /**
     * **Warning:** The creator will be the owner of the application and must free it.
     */
    static ClientApplication* CreateWithWebSocket(ServerConnectionInfo& info){
        BasicClientApplication *app = new BasicClientApplication();
        SocketClient *socket = new WebSocketClient(info, *app);
        app->setSocket(socket);
        return app;
    }

    /**
     * **Warning:** The creator will be the owner of the application and must free it.
     */
    static ClientApplication* CreateWithMockUpSocket(ServerConnectionInfo& info){
        BasicClientApplication *app = new BasicClientApplication();
        SocketClient *socket = new MockUpSocketClient(info, *app);
        app->setSocket(socket);
        return app;
    }
};

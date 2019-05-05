#pragma once

#include "client/application/BasicClientApplication.hpp"
#include "client/network/ServerConnectionInfo.hpp"
#include "MockUpSocketClient.hpp"

/**
 * Factory for tests
 */
class ClientApplicationFactory {
public:
    /**
     * Implementation with a mock-up on the socket that does not connect to
     *  any actual server. Can be useful for test purpose and debugging.
     *
     * @return **Warning:** The creator will be the owner of the application and
     *  must free it.
     */
    static ClientApplication* CreateWithWebSocket(ServerConnectionInfo& info){
        BasicClientApplication *app = new BasicClientApplication();
        SocketClient *socket = new MockUpSocketClient(info, *app);
        app->setSocket(socket);
        return app;
    }
};
